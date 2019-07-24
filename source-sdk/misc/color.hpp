#pragma once
#include <cstdint>
#include <d3d9.h>

#pragma once
#include <cstdint>
#include <d3d9.h>


struct color
{
	 int r, g, b, a;
	color() = default;
	

		color(int r, int g, int b, int a = 255) {
		 this->r = r;
		 this->g = g;
		 this->b = b;
		 this->a = a;
	}



	constexpr color& FromHSV(float h, float s, float v)
	{
		float colOut[3]{ };
		if (s == 0.0f)
		{
			r = g = b = static_cast<int>(v * 255);
			return *this;
		}

		h = std::fmodf(h, 1.0f) / (60.0f / 360.0f);
		int   i = static_cast<int>(h);
		float f = h - static_cast<float>(i);
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i)
		{
		case 0:
			colOut[0] = v;
			colOut[1] = t;
			colOut[2] = p;
			break;
		case 1:
			colOut[0] = q;
			colOut[1] = v;
			colOut[2] = p;
			break;
		case 2:
			colOut[0] = p;
			colOut[1] = v;
			colOut[2] = t;
			break;
		case 3:
			colOut[0] = p;
			colOut[1] = q;
			colOut[2] = v;
			break;
		case 4:
			colOut[0] = t;
			colOut[1] = p;
			colOut[2] = v;
			break;
		case 5: default:
			colOut[0] = v;
			colOut[1] = p;
			colOut[2] = q;
			break;
		}

		r = static_cast<int>(colOut[0] * 255);
		g = static_cast<int>(colOut[1] * 255);
		b = static_cast<int>(colOut[2] * 255);

		return *this;
	}

		color(float* clr) {
		this->r = clr[0];
		this->g = clr[1];
		this->b = clr[2];
		this->a = clr[3];
	}

};