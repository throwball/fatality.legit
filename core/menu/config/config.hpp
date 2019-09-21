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
		//Aimbot / BT
		float backtrack_ms{ 0.0f };
		bool backtrack{ false };
		//Misc
		bool misc_enabled{ false };
		bool Bhop{ false };
		//Colorpicker
		zgui::color2 box_clr{ 255, 255, 255, 255 };
		// Visuals
		bool player_dormant{ false };
		int player_box;
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