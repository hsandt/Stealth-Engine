//
// Created by acro_ on 2016/06/24.
//

#pragma once

/// RGBA color
struct Color
{
public:
	Color() : r(0), g(0), b(0), a(1) {}

	Color (float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	float r;
	float g;
	float b;
	float a;
};

