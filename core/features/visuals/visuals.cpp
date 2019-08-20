#include "visuals.hpp"
#include "../../../dependencies/math/math.hpp"
#include "../../../source-sdk/classes/entities.hpp"


#define TIME_TO_TICKS(dt) ((int)( 0.5f + (float)(dt) / interfaces::globals->interval_per_tick))

c_visuals visuals;

void c_visuals::run() noexcept
{
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	if (!c_system.cfg.visuals_enabled)
		return;

	if (!local_player)
		return;

	//player drawing loop
	for (int i = 1; i <= interfaces::globals->max_clients; i++)
	{
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
	
		if (!entity)
			continue;

		if (entity == local_player)
			continue;

		if (entity->health() <= 0)
			continue;

		if (entity->team() == local_player->team() && !c_system.cfg.visuals_team_check)
			continue;


		const int fade = (int)((6.66666666667f * interfaces::globals->frame_time) * 255);

		auto new_alpha = alpha[i];
		new_alpha += entity->dormant() ? -fade : fade;

		if (new_alpha > (entity->has_gun_game_immunity() ? 130 : 210))
			new_alpha = (entity->has_gun_game_immunity() ? 130 : 210);
		if (new_alpha < c_system.cfg.player_dormant ? 50 : 0)
			new_alpha = c_system.cfg.player_dormant ? 50 : 0;

		alpha[i] = new_alpha;

		player_rendering(entity);
		skeleton(entity);
		last_dormant[i] = entity->dormant();
	}

	//non player drawing loop
	for (int i = 0; i < interfaces::entity_list->get_highest_index(); i++) {
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (entity && entity != local_player) {
			auto client_class = entity->clientclass();
			auto model_name = interfaces::model_info->get_model_name(entity->model());

			entity_esp(entity);
		}
	}
}

void c_visuals::entity_esp(player_t* entity) noexcept {
	//if (!c_system.cfg.entity_esp)
	//	return;

//	if (!entity)
	//	return;

	//if (entity->dormant())
		//return;

//	auto model_name = interfaces::model_info->get_model_name(entity->model());
	//vec3_t entity_position, entity_origin;
	//entity_origin = entity->origin();
	//auto client_class = entity->client_class1();

/*	if (!math.world_to_screen(entity_origin, entity_position))
		return;

	if (client_class->class_id == class_ids::cchicken) {
		render::text(entity_position.x, entity_position.y, render::main_font, "chicken", true, Color(255, 255, 255));
	}

	else if (strstr(model_name, "dust_soccer_ball001")) {
		render::text(entity_position.x, entity_position.y, render::main_font, "soccer ball", true, Color(255, 255, 255));
	}

	else if (client_class->class_id == class_ids::chostage) {
		render::text(entity_position.x, entity_position.y, render::main_font, "hostage", true, Color(255, 255, 255));
	}*/
}

void c_visuals::skeleton(player_t* entity) noexcept {
	if (!c_system.cfg.skeleton)
		return;

	auto p_studio_hdr = interfaces::model_info->get_studio_model(entity->model());

	if (!p_studio_hdr)
		return;

	vec3_t v_parent, v_child, s_parent, s_child;

	for (int i = 0; i < p_studio_hdr->bones_count; i++) {
		studio_bone_t* bone = p_studio_hdr->bone(i);

		if (!bone)
			return;

		if (bone && (bone->flags & bone_used_by_hitbox) && (bone->parent != -1)) {
			v_child = entity->get_bone_position(i);
			v_parent = entity->get_bone_position(bone->parent);

			if (math.world_to_screen(v_parent, s_parent) && math.world_to_screen(v_child, s_child))
				render::line(s_parent[0], s_parent[1], s_child[0], s_child[1], Color(255, 255, 255, alpha[entity->index()]));
		}
	}
}


void c_visuals::player_rendering(player_t* entity) noexcept
{
	color = Color(c_system.cfg.box_clr.r, c_system.cfg.box_clr.g, c_system.cfg.box_clr.b, c_system.cfg.box_clr.a);
	if ((entity->dormant() && alpha[entity->index()] == 0) && !c_system.cfg.player_dormant)
		return;

	player_info_t info;
	interfaces::engine->get_player_info(entity->index(), &info);

	box bbox;
	if (!get_playerbox(entity, bbox))
		return;



	if (c_system.cfg.player_box == 1) {
		// normal box
		render::rect(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, Color(c_system.cfg.box_clr.r, c_system.cfg.box_clr.g, c_system.cfg.box_clr.b + alpha[entity->index()]));
	}
		//edge
	if (c_system.cfg.player_box == 2) {
		render::draw_corner_box(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, Color(0, 0, 0, 255 + alpha[entity->index()]));
		render::draw_corner_box(bbox.x, bbox.y, bbox.w, bbox.h, Color(c_system.cfg.box_clr.r, c_system.cfg.box_clr.g, c_system.cfg.box_clr.b, 255 + alpha[entity->index()]));
		render::draw_corner_box(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, Color(0, 0, 0, 255 + alpha[entity->index()]));
	}

	if (c_system.cfg.player_health) {
		box temp(bbox.x - 5, bbox.y + (bbox.h - bbox.h * (utilities::math::clamp_value<int>(entity->health(), 0, 100.f) / 100.f)), 1, bbox.h * (utilities::math::clamp_value<int>(entity->health(), 0, 100) / 100.f) - (entity->health() >= 100 ? 0 : -1));
		box temp_bg(bbox.x - 5, bbox.y, 1, bbox.h);

		auto health_color = Color((255 - entity->health() * 2.55), (entity->health() * 2.55), 0, alpha[entity->index()]);

		if (entity->health() > 100)
			health_color = Color(0, 255, 0);

		render::filled_rect(temp_bg.x - 1, temp_bg.y - 1, temp_bg.w + 2, temp_bg.h + 2, Color(0, 0, 0, 25 + alpha[entity->index()]));
		render::filled_rect(temp.x, temp.y, temp.w, temp.h, Color(health_color));
	}
	 

	
}
