#pragma once
#include "../../../dependencies/common_includes.hpp"
#include <filesystem>

class c_system : public singleton< c_system > {
public:
	int counts;
	bool save_config(std::string file_name);
	bool load_config(std::string file_name);
	bool remove_config(std::string file_name);
	void create_config(std::string name);
	std::vector<std::string> get_configs();

	struct {
		bool player_dormant{ false };
		bool visuals_team_check{ false };
		bool player_box{ false };
		bool Bhop{ false };
		bool nade_pred = false;
		bool grenade_prediction = false;
		//colorv2 clr_grenadepred;
		bool visuals_enabled{ false };
		bool misc_enabled{ false };
		float clr_box[4]{ 1.0f,1.0f,1.0f,1.0f };
	};
};