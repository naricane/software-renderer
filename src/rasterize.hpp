#pragma once

#include "color.hpp"
#include "data_types.hpp"
#include "math.hpp"

namespace rasterize {

void
put_pixel(FrameBuffer& fb, Vec2i position, Color color);

void
plot_line(FrameBuffer& fb, Vec2i from, Vec2i to);

void
fill_triangle(
	FrameBuffer& fb,
	Vec2i a,
	Vec2i b,
	Vec2i c,
	float depth_a,
	float depth_b,
	float depth_c,
	Color color_a,
	Color color_b,
	Color color_c
);

}
