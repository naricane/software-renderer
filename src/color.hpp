#pragma once
#include <cstdint>

struct Color
{
	uint8_t r = 0x0;
	uint8_t g = 0x0;
	uint8_t b = 0x0;
	uint8_t a = 0xFF;

	uint32_t packed() { return a << 24 | b << 16 | g << 8 | r; }
};
