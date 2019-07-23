#pragma once
#include "misc.hpp"

cmovement movement;

void cmovement::Bhop(c_usercmd* user_cmd) noexcept
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