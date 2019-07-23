#pragma once
#include "misc.hpp"

cmisc misc;

void cmisc::Bhop(c_usercmd* user_cmd) noexcept
{
	if (!c_system.Bhop || !c_system.misc_enabled)
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (!local_player)
		return;

	if (local_player->move_type() == movetype_ladder || local_player->move_type() == movetype_noclip)
		return;

	if (user_cmd->buttons & in_jump && !(local_player->flags() & fl_onground))
	{
		user_cmd->buttons &= ~in_jump;
	}
}

void cmisc::spectatorlist() noexcept
{

	if (!c_system.speclist || !c_system.misc_enabled)
		return;

	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	int spectator_index = 0;
	int width, height;
	interfaces::engine->get_screen_size(width, height);

	render::text(width - 80, height / 2 - 10, color(255, 255, 255), render::main_font, true, "spectators");
	for (int i = 0; i < interfaces::entity_list->get_highest_index(); i++) {
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		if (!local_player)
			return;

		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity)
			return;

		player_info_t info;

		if (entity && entity != local_player) {
			interfaces::engine->get_player_info(i, &info);
			if (!entity->is_alive() && !entity->dormant()) {
				auto target = entity->observer_target();

				if (!target)
					return;

				if (target) {
					auto spectator_target = interfaces::entity_list->get_client_entity_handle(target);
					if (spectator_target == local_player) {
						std::string player_name = info.name;
						std::transform(player_name.begin(), player_name.end(), player_name.begin(), ::tolower);
						player_info_t spectator_info;
						interfaces::engine->get_player_info(i, &spectator_info);
						render::text(width - 80, height / 2 + (10 * spectator_index), color(255, 255, 255), true, render::main_font, player_name.c_str());
						spectator_index++;
					}
				}
			}
		}
	}
}

