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

		// Visuals
		bool player_dormant{ false };
		bool player_box{ false };
		zgui::color2 box_clr{ 255, 255, 255, 255 };

		bool visuals_team_check{ false };
		bool visuals_enabled{ false };
	} cfg;

private:
	std::filesystem::path path;
	std::vector<std::string> configs;


};

extern cconfig c_system;