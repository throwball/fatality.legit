#pragma once
#include "../zgui/zgui.hpp"
#include <filesystem>

class cconfig final {
public:
	void run(const char*) noexcept;
	void load(size_t) noexcept;
	void save(size_t) const noexcept;
	void add(const char*) noexcept;
	void remove(size_t) noexcept;
	void rename(size_t, const char*) noexcept;
	void reset() noexcept;

	constexpr auto& get_configs() noexcept {
		return configs;
	}

	struct {
		//Misc
		bool misc_enabled{ false };
		bool Bhop{ false };
		//Colorpicker
		zgui::color2 box_clr{ 255, 255, 255, 255 };
		zgui::color2 clr_glow{ 255, 255, 255, 255 };
		zgui::color2 clr_glow_team{ 255, 255, 255, 255 };
		zgui::color2 clr_glow_planted{ 255, 255, 255, 255 };
		zgui::color2 clr_glow_dropped{ 255, 255, 255, 255 };
		// Visuals
		bool player_dormant{ false };
		int player_box;
		bool visuals_glow{ false };
		bool visuals_glow_enemy{ false };
		bool visuals_glow_team{ false };
		bool visuals_glow_planted{ false };
		bool visuals_glow_weapons{ false };
		bool skeleton{ false };
		bool visuals_team_check{ false };
		bool visuals_enabled{ false };
		bool player_health{ false };

	} cfg;

private:
	std::filesystem::path path;
	std::vector<std::string> configs;


};

extern cconfig c_system;