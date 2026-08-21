#include "framebuffer.hpp"
#include "constants.hpp"

Framebuffer::Framebuffer()
	: pixels(WIDTH * HEIGHT, 0x0)
{
}

void
Framebuffer::clear()
{
	std::fill(pixels.begin(), pixels.end(), 0x0);
}

std::span<uint32_t>
Framebuffer::get_pixels()
{
	return std::span{ pixels };
}
