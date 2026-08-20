#include "framebuffer.hpp"
#include "constants.hpp"

Framebuffer::Framebuffer()
	: pixels(WIDTH * HEIGHT, 0x0)
{
}

uint32_t*
Framebuffer::get_pixels()
{
	return pixels.data();
}
