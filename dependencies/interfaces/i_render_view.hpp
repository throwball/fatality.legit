#pragma once
#include "../../source-sdk/misc/color.hpp"

class i_render_view {
private:
	virtual void __pad0();
	virtual void __pad1();
	virtual void __pad2();
	virtual void __pad3();

public:
	virtual void set_blend(zgui::color2 blend) = 0;

	virtual void modulate_color(zgui::color2 blend) = 0;
	virtual void get_color_modulation(zgui::color2 blend) = 0;
};

struct view_setup_t {
	char __pad0[0xB0];
	float fov;
	float viewmodel_fov;
};