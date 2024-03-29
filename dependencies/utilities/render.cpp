#include "render.hpp"
unsigned long render::main_font;

void render::setup_fonts() {
	main_font = interfaces::surface->font_create();

	interfaces::surface->set_font_glyph(main_font, "Minecraft", 12, 500, 0, 0, font_flags::fontflag_outline);
}



void render::line(int x, int y, int x2, int y2, Color c) noexcept {
	interfaces::surface->set_drawing_color(c.r, c.g, c.b, c.a);
	interfaces::surface->draw_line(x, y, x2, y2);
}

void render::corner_box(int x, int y, int w, int h, Color c) {
	interfaces::surface->set_drawing_color(c.r, c.g, c.b, c.a);
	interfaces::surface->draw_line(x, y, x, y + (h / 5));
	interfaces::surface->draw_line(x, y, x + (w / 5), y);
	interfaces::surface->draw_line(x + w, y, x + w - (w / 5), y);
	interfaces::surface->draw_line(x + w, y, x + w, y + (h / 5));
	interfaces::surface->draw_line(x, y + h, x + (w / 5), y + h);
	interfaces::surface->draw_line(x, y + h, x, y + h - (h / 5));
	interfaces::surface->draw_line(x + w, y + h, x + w - (w / 5), y + h);
	interfaces::surface->draw_line(x + w, y + h, x + w, y + h - (h / 5));
}

void render::rect(int x, int y, int x2, int y2, Color c) noexcept {
	interfaces::surface->set_drawing_color(c.r, c.g, c.b, c.a);
	interfaces::surface->draw_outlined_rect(x, y, x2, y2);
}

void render::filled_rect(int x, int y, int x2, int y2, Color c) noexcept {
	interfaces::surface->set_drawing_color(c.r, c.g, c.b, c.a);
	interfaces::surface->draw_filled_rectangle(x, y, x2, y2);
}

void render::text(int x, int y, Color color, int font, bool center, std::string str) noexcept {
	std::wstring text = std::wstring(str.begin(), str.end());
	const wchar_t* converted_text = text.c_str();

	int width, height;
	interfaces::surface->get_text_size(font, converted_text, width, height);

	interfaces::surface->set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_text_font(font);
	if (center)
		interfaces::surface->draw_text_pos(x - (width / 2), y);
	else
		interfaces::surface->draw_text_pos(x, y);

	interfaces::surface->draw_render_text(converted_text, wcslen(converted_text));
}

void render::get_text_size(unsigned long font, std::string str, int& width, int& height) noexcept {
	std::wstring text = std::wstring(str.begin(), str.end());
	const wchar_t* out = text.c_str();

	interfaces::surface->get_text_size(font, out, width, height);
}

float render::get_frametime() noexcept {
	return interfaces::globals->frametime;
}