#pragma once

#include <cstdint>
#include <span>
#include <vector>

class Framebuffer
{
private:
	std::vector<uint32_t> pixels;

public:
	Framebuffer();
	std::span<uint32_t> get_pixels();
};
