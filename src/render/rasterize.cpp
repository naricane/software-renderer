#include "rasterize.hpp"
#include "constants.hpp"
#include <algorithm>
#include <cstdlib>

namespace rasterize {

void
put_pixel(FrameBuffer& fb, Vec2i position, Color color)
{
	if (position.x < 0 || position.x >= WIDTH || position.y < 0 || position.y >= HEIGHT) {
		return;
	}
	fb.get_span()[position.x + position.y * WIDTH] = color;
}

/* cool explanation: https://www.youtube.com/watch?v=CceepU1vIKo */
void
plot_line_h(FrameBuffer& fb, Vec2i from, Vec2i to)
{
	if (from.x > to.x) {
		std::swap(from.x, to.x);
		std::swap(from.y, to.y);
	}

	Vec2i d = { to.x - from.x, to.y - from.y };

	int dir = d.y < 0 ? -1 : 1;
	d.y *= dir;

	if (d.x != 0) {
		int y = from.y;
		int p = 2 * d.y - d.x;

		for (int i = 0; i < d.x + 1; i++) {
			put_pixel(fb, { from.x + i, y }, Color{ 255, 255, 255 });

			if (p >= 0) {
				y += dir;
				p = p - 2 * d.x;
			}
			p = p + 2 * d.y;
		}
	}
}

void
plot_line_v(FrameBuffer& fb, Vec2i from, Vec2i to)
{
	if (from.y > to.y) {
		std::swap(from.x, to.x);
		std::swap(from.y, to.y);
	}

	Vec2i d = { to.x - from.x, to.y - from.y };

	int dir = d.x < 0 ? -1 : 1;
	d.x *= dir;

	if (d.y != 0) {
		int x = from.x;
		int p = 2 * d.x - d.y;

		for (int i = 0; i < d.y + 1; i++) {
			put_pixel(fb, { x, from.y + i }, Color{ 255, 255, 255 });

			if (p >= 0) {
				x += dir;
				p = p - 2 * d.y;
			}
			p = p + 2 * d.x;
		}
	}
}

void
plot_line(FrameBuffer& fb, Vec2i from, Vec2i to)
{
	if (std::abs(to.x - from.x) > std::abs(to.y - from.y)) {
		plot_line_h(fb, from, to);
	} else {
		plot_line_v(fb, from, to);
	}
}

static float
edge_function(Vec2i a, Vec2i b, Vec2i c)
{
	return .5f * ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

/* cool tutorial: https://jtsorlinis.github.io/rendering-tutorial/ */
void
fill_triangle(
	FrameBuffer& fb,
	ZBuffer& zb,
	Vec2i a,
	Vec2i b,
	Vec2i c,
	float depth_a,
	float depth_b,
	float depth_c,
	Color color_a,
	Color color_b,
	Color color_c
)
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

				float depth = depth_a * weight_a + depth_b * weight_b + depth_c * weight_c;

				float& zb_cell = zb.get_span()[x + y * WIDTH];
				if (depth >= zb_cell) {
					continue;
				}
				zb_cell = depth;

				uint8_t rr = color_a.r * weight_a + color_b.r * weight_b + color_c.r * weight_c;
				uint8_t gg = color_a.g * weight_a + color_b.g * weight_b + color_c.g * weight_c;
				uint8_t bb = color_a.b * weight_a + color_b.b * weight_b + color_c.b * weight_c;
				Color color = Color{ rr, gg, bb };

				put_pixel(fb, Vec2i{ p.x, p.y }, color);
			}
		}
	}
}

}
