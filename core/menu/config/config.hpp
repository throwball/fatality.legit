#pragma once

#include <filesystem>

class cconfig final {
public:
	void run(const char*) noexcept;
	void load(size_t) noexcept;
	void save(size_t) const noexcept;
	void add(const char*) noexcept;
	void remove(size_t) noexcept;
	void rename(size_t, const char*) noexcept;


	constexpr auto& get_configs() noexcept {
		return configs;

	}

	struct {
		bool player_dormant{ false };
		bool visuals_team_check{ false };
		bool player_box{ false };
		bool Bhop{ false };
		bool visuals_enabled{ false };
		bool misc_enabled{ false };
	};

private:
	std::filesystem::path path;
	std::vector<std::string> configs;
};

extern cconfig c_system;