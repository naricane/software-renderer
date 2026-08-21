#pragma once

#include "framebuffer.hpp"
#include "math.hpp"

namespace rasterize {

void
put_pixel(Framebuffer& fb, Vec2i position, uint32_t color);

void
plot_line(Framebuffer& fb, Vec2i from, Vec2i to);

void
fill_triangle(Framebuffer& fb, Vec2i a, Vec2i b, Vec2i c);

}
