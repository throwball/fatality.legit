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
	static bool stuff1;
	static float sliderf;
	static int slideri, dropdown;
	//tab defs
	void visuals();
	void misc();
	void stuff();

	zgui::poll_input("Counter-Strike: Global Offensive");

	// beginning of menu

	if (zgui::begin_window("Fatality.Legit", { 500, 350 }, render::main_font, zgui::zgui_window_flags_none)) {

		zgui::push_font(render::main_font);

		if (zgui::tab_button("visualities", { 150, 30 }, visuals1))
		{

			visuals1 = true;
			misc1 = false;
			stuff1 = false;
		}

		zgui::next_column(164, -0.5);

		if (zgui::tab_button("miscilities", { 150, 30 }, misc1))
		{
			misc1 = true;
			visuals1 = false;
			stuff1 = false;
		}

		zgui::next_column(164, -5);

		if (zgui::tab_button("stuffiltiies", { 150, 30 }, stuff1))
		{
			misc1 = false;
			visuals1 = false;
			stuff1 = true;
		}

		if (misc1) misc();
		if (stuff1) stuff();
		if (visuals1) visuals();

		zgui::pop_font();
		zgui::end_window();

	}

}

void visuals()
{
	static bool checkbox;

	zgui::next_column(-163, 38);

	zgui::begin_groupbox("visuals", { 250, 110 }, render::main_font); 
	{
		zgui::checkbox("active", c_system.cfg.visuals_enabled);
		zgui::checkbox("team esp", c_system.cfg.visuals_team_check);
		zgui::checkbox("dormant check", c_system.cfg.player_dormant);
		zgui::checkbox("skeleton esp", c_system.cfg.skeleton);
		zgui::checkbox("health esp", c_system.cfg.player_health);

		zgui::next_column(-8, 140);

		zgui::begin_groupbox("visuals stuff", { 250, 100 }, render::main_font); 
		{
			zgui::combobox("box esp",  { "off", "normal",  "edge" }, c_system.cfg.player_box);


		//	zgui::checkbox("nade pred", c_system::get().nade_pred);
			//zgui::colorpicker("nade pred colors", c_system::get().clr_grenadepred);
		}

	}
	zgui::end_groupbox();
}

void stuff()
{
	static bool checkbox;
	zgui::next_column(-163, 38);
	zgui::begin_groupbox("colors", { 250,100 }, render::main_font); {
		zgui::text("box esp color");
		zgui::colorpicker("box esp color", c_system.cfg.box_clr);
		//zgui::text("glow esp color");
		//zgui::colorpicker("glow esp color", c_system.cfg.clr_glow);
		//zgui::text("dropped weapon glow clr");
		//zgui::colorpicker("dropped color", c_system.cfg.clr_glow_dropped);
		//zgui::text("planted bomb glow clr");
	//	zgui::colorpicker("glow clr", c_system.cfg.clr_glow_planted);

		
	}
	zgui::end_groupbox();
}

void misc()
{
	static bool checkbox;
	zgui::next_column(-163,  38);
	zgui::begin_groupbox("misc", { 250, 100 }, render::main_font); {
		zgui::checkbox("active", c_system.cfg.misc_enabled);
		zgui::checkbox("bhop", c_system.cfg.Bhop);

	}
		zgui::end_groupbox();
}
