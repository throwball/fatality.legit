#include "menu.hpp"
#include "../menu/config/config.hpp"

//	note from alpha:
//	i strongly suggest people to use namespaces insteas of classes and singletons
//	not only is it a bad habit, i overused singletons in this sdk, and they're not thread safe.

void menu::render() 
{
	//defs for checkbox etc.
	static bool checkbox;
	static bool visuals1;
	static bool misc1;
	static float sliderf;
	static int slideri, dropdown;
	//tab defs
	void visuals();
	void misc();

	zgui::poll_input("Counter-Strike: Global Offensive");

	// beginning of menu

	if (zgui::begin_window("Fatality.Legit", { 500, 350 }, render::main_font, zgui::zgui_window_flags_none)) {

		zgui::push_font(render::main_font);

		if (zgui::tab_button("visualities", { 150, 30 }, visuals1))
		{

			visuals1 = true;
			misc1 = false;
		}

		zgui::next_column(164, -0.5);

		if (zgui::tab_button("miscilities", { 150, 30 }, misc1))
		{
			misc1 = true;
			visuals1 = false;
		}

		if (misc1) misc();
		if (visuals1) visuals();

		zgui::pop_font();
		zgui::end_window();

	}

}

void visuals()
{
	static bool checkbox;
	zgui::next_column(-163, 38);
	zgui::begin_groupbox("visuals", { 250, 100 }, render::main_font); {
		zgui::checkbox("active", c_system.visuals_enabled);
		zgui::checkbox("team esp", c_system.visuals_team_check);
		zgui::checkbox("dormant check", c_system.player_dormant);
		zgui::checkbox("box esp", c_system.player_box);

	}
	zgui::end_groupbox();
}

void misc()
{
	static bool checkbox;
	zgui::next_column(-163,  38);
	zgui::begin_groupbox("misc", { 250, 100 }, render::main_font); {
		zgui::checkbox("active", c_system.misc_enabled);
		zgui::checkbox("bhop", c_system.Bhop);
		zgui::checkbox("spectator list", c_system.speclist);
	}
		zgui::end_groupbox();
}
