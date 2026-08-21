#include "rasterize.hpp"
#include "constants.hpp"
#include "framebuffer.hpp"
#include <cstdlib>

namespace rasterize {

void
put_pixel(Framebuffer& fb, Vec2i position, uint32_t color)
{
	if (position.x < 0 || position.x >= WIDTH || position.y < 0 || position.y >= HEIGHT) {
		return;
	}
	fb.get_pixels()[position.x + position.y * WIDTH] = color;
}

/* cool explanation: https://www.youtube.com/watch?v=CceepU1vIKo */
void
plot_line_h(Framebuffer& fb, Vec2i from, Vec2i to)
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
			put_pixel(fb, { from.x + i, y }, LINE_COLOR);

			if (p >= 0) {
				y += dir;
				p = p - 2 * d.x;
			}
			p = p + 2 * d.y;
		}
	}
}

void
plot_line_v(Framebuffer& fb, Vec2i from, Vec2i to)
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
			put_pixel(fb, { x, from.y + i }, LINE_COLOR);

			if (p >= 0) {
				x += dir;
				p = p - 2 * d.y;
			}
			p = p + 2 * d.x;
		}
	}
}

void
plot_line(Framebuffer& fb, Vec2i from, Vec2i to)
{
	if (std::abs(to.x - from.x) > std::abs(to.y - from.y)) {
		plot_line_h(fb, from, to);
	} else {
		plot_line_v(fb, from, to);
	}
}

}
