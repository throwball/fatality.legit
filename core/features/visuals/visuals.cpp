#include "visuals.hpp"
#include "../../../dependencies/math/math.hpp"


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

		player_rendering(entity);

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

void c_visuals::entity_esp(player_t* entity) noexcept
{
	auto model = entity->model();
	if (!model)
		return;

	if (model) {
		vec3_t entity_position, entity_origin;
		entity_origin = entity->origin();
		auto client_class = entity->clientclass();
		auto model = interfaces::model_info->get_studio_model(entity->model());
		if (!model)
			return;
		if (!math.world_to_screen(entity_origin, entity_position))
			return;

		std::string name = model->name_char_array, drop_name;

		//if (name.find("dust_soccer_ball001") != std::string::npos) {
	//		drop_name = "soccer ball";
		//}
	//	if (client_class->class_id == class_ids::cchicken) {
		//	drop_name = "chicken";
	//	}
	//	else if (client_class->class_id == class_ids::chostage) {
	//	drop_name = "hostage";
	//	}
		render::text(entity_position.x, entity_position.y, color(255, 255, 255), render::main_font, true, drop_name.c_str());
		//render.draw_text(entity_position.x, entity_position.y, render::main_font, drop_name.c_str(), true, color(255, 255, 255));
	}
}

void c_visuals::player_rendering(player_t* entity) noexcept
{
	if ((entity->dormant() && alpha[entity->index()] == 0) && !c_system.cfg.player_dormant)
		return;

	player_info_t info;
	interfaces::engine->get_player_info(entity->index(), &info);

	box bbox;
	if (!get_playerbox(entity, bbox))
		return;

	if (c_system.cfg.player_box) {

		 auto r = c_system.cfg.clr_box[0];
		 auto g = c_system.cfg.clr_box[1];
		 auto b = c_system.cfg.clr_box[2];

		render::rect(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, color(0, 0, 0, 255 + alpha[entity->index()]));
		render::rect(bbox.x, bbox.y, bbox.w, bbox.h, color(r, g, b, alpha[entity->index()]));
		render::rect(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, color(0, 0, 0, 255 + alpha[entity->index()]));
	}

}
