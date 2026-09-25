#pragma once

#include "core/color.hpp"
#include "core/constants.hpp"
#include "core/data_types.hpp"
#include "core/math.hpp"

namespace rasterize {

void
put_pixel(ColorBuffer& fb, Vec2i position, Color color);

void
plot_line(ColorBuffer& fb, Vec2i from, Vec2i to);

inline float
edge_function(Vec2i a, Vec2i b, Vec2i c)
{
	return .5f * ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

/* cool tutorial: https://jtsorlinis.github.io/rendering-tutorial/ */
template<typename PerPixelFn>
void
fill_triangle(Vec2i a, Vec2i b, Vec2i c, PerPixelFn&& fn)
{
	float ABC = edge_function(a, b, c);

	if (ABC >= 0) {
		return;
	}

	int min_x = std::min(std::min(a.x, b.x), c.x);
	int min_y = std::min(std::min(a.y, b.y), c.y);
	int max_x = std::max(std::max(a.x, b.x), c.x);
	int max_y = std::max(std::max(a.y, b.y), c.y);

	float inv_area = 1.0 / ABC;

#pragma omp parallel for
	for (int y = std::max(min_y, 0); y < std::min(max_y, HEIGHT); ++y) {
		for (int x = std::max(min_x, 0); x < std::min(max_x, WIDTH); ++x) {
			Vec2i p{ x, y };
			float ABP = edge_function(a, b, p);
			float BCP = edge_function(b, c, p);
			float CAP = edge_function(c, a, p);

			if (ABP <= 0 && BCP <= 0 && CAP <= 0) {
				float weight_a = BCP * inv_area;
				float weight_b = CAP * inv_area;
				float weight_c = ABP * inv_area;

				fn(x, y, weight_a, weight_b, weight_c);
			}
		}
	}
}

}
