#pragma once
#include "..//menu/menu.hpp"
#include "../../dependencies/common_includes.hpp"
#include <algorithm>
#include "../features/visuals/visuals.hpp"
#include "../features/misc/misc.hpp"
#include "../menu/zgui/zgui.hpp"
#include "../features/backtrack/backtrack.hpp"

std::unique_ptr<vmt_hook> hooks::client_hook;
std::unique_ptr<vmt_hook> hooks::clientmode_hook;
std::unique_ptr<vmt_hook> hooks::panel_hook;
std::unique_ptr<vmt_hook> hooks::renderview_hook;
std::unique_ptr<vmt_hook> hooks::surface_hook;

WNDPROC hooks::wndproc_original = NULL;

void hooks::initialize( ) {
	client_hook = std::make_unique<vmt_hook>( );
	clientmode_hook = std::make_unique<vmt_hook>( );
	panel_hook = std::make_unique<vmt_hook>( );
	renderview_hook = std::make_unique<vmt_hook>( );
	surface_hook = std::make_unique<vmt_hook>(interfaces::surface);

	client_hook->setup( interfaces::client );
	client_hook->hook_index( 37, reinterpret_cast< void* >( frame_stage_notify ) );

	clientmode_hook->setup( interfaces::clientmode );
	clientmode_hook->hook_index( 24, reinterpret_cast< void* >( create_move ) );

	panel_hook->setup( interfaces::panel );
	panel_hook->hook_index( 41, reinterpret_cast< void* >( paint_traverse ) );

	renderview_hook->setup( interfaces::render_view );
	renderview_hook->hook_index( 9, reinterpret_cast< void* >( scene_end ) );

	surface_hook->setup(interfaces::surface);
	surface_hook->hook_index(67, reinterpret_cast<void* >( lock_cursor ) );

	wndproc_original = ( WNDPROC ) SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc );

	interfaces::console->get_convar( "mat_queue_mode" )->set_value( 0 );
	interfaces::console->get_convar( "viewmodel_fov" )->callbacks.SetSize( 0 );
	interfaces::console->get_convar( "mat_postprocess_enable" )->set_value( 0 );
	interfaces::console->get_convar( "crosshair" )->set_value( 1 );

	render::setup_fonts( );
	//1
	zgui::functions.draw_line = render::line;
	zgui::functions.draw_rect = render::rect;
	zgui::functions.draw_filled_rect = render::filled_rect;
	zgui::functions.draw_text = render::text;
	zgui::functions.get_text_size = render::get_text_size;
	zgui::functions.get_frametime = render::get_frametime;
}

void hooks::shutdown( ) {
	clientmode_hook->release( );
	client_hook->release( );
	panel_hook->release( );
	renderview_hook->release( );

	SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc_original );
}

bool __stdcall hooks::create_move( float frame_time, c_usercmd* user_cmd ) {

	static auto original_fn = reinterpret_cast<create_move_fn>(clientmode_hook->get_original(24));
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	original_fn(interfaces::clientmode, frame_time, user_cmd); //fixed create move
	bool& send_packet = *reinterpret_cast<bool*>(*(static_cast<uintptr_t*>(_AddressOfReturnAddress()) - 1) - 0x1C);

	if (!user_cmd || !user_cmd->command_number)
		return original_fn;

	if (!interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()))
		return original_fn;

	backtrack.run(user_cmd);

	if (interfaces::engine->is_connected() && interfaces::engine->is_in_game())
	{

		misc.Bhop(user_cmd);

	}

	return false;
}

void __stdcall hooks::frame_stage_notify( int frame_stage ) {
	reinterpret_cast< frame_stage_notify_fn >( client_hook->get_original( 37 ) )( interfaces::client, frame_stage );
	static auto backtrack_init = (backtrack.init(), false);

		 if (frame_stage == interfaces::engine->is_in_game()) {
		backtrack.update();
	}
}

void __stdcall hooks::paint_traverse( unsigned int panel, bool force_repaint, bool allow_force ) {
	std::string panel_name = interfaces::panel->get_panel_name( panel );

	reinterpret_cast< paint_traverse_fn >( panel_hook->get_original( 41 ) )( interfaces::panel, panel, force_repaint, allow_force );

	static unsigned int _panel = 0;
	static bool once = false;

	if ( !once ) {
		PCHAR panel_char = ( PCHAR ) interfaces::panel->get_panel_name( panel );
		if ( strstr( panel_char, "MatSystemTopPanel" ) ) {
			_panel = panel;
			once = true;
		}
	}
	else if ( _panel == panel ) {
		visuals.run();
		menu::render();
	}
}

void __stdcall hooks::scene_end( )
{
	reinterpret_cast< scene_end_fn >( renderview_hook->get_original( 9 ) )( interfaces::render_view );
}

void __fastcall hooks::lock_cursor(i_surface* thisptr, void* edx)
{
	static auto ohook = reinterpret_cast<lock_cursor_fn>(surface_hook->get_original(67));
	if (menu_open == true) {
		interfaces::surface->unlock_cursor();
		return;
	}
	ohook(thisptr, edx);
}

LRESULT __stdcall hooks::wndproc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) 
{
	if (menu_open)
	{
		interfaces::inputsystem->enable_input(false);
	}
	else if (!menu_open)
	{
		interfaces::inputsystem->enable_input(true);
	}
	return CallWindowProcA( wndproc_original, hwnd, message, wparam, lparam );
}
