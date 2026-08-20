#pragma once

#include <cstdint>
#include <vector>

class Framebuffer
{
private:
	std::vector<uint32_t> pixels;

public:
	Framebuffer();
	uint32_t* get_pixels();
};
