#pragma once
#include <cstdint>
#include <d3d9.h>

struct Color {
	int a, r, g, b;
	Color() = default;
	Color(int r, int g, int b, int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	Color(uint32_t Color) {
		this->a = (Color >> 24) & 0xff;
		this->r = (Color >> 16) & 0xff;
		this->g = (Color >> 8) & 0xff;
		this->b = (Color & 0xff);
	}
	Color from_uint(uint32_t uint) {
		return Color(uint);
	}
	D3DCOLOR from_color(Color col) {
		return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
	}
};