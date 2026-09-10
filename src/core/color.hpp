#pragma once
#include <cstdint>

struct Color
{
	uint8_t r = 0x0;
	uint8_t g = 0x0;
	uint8_t b = 0x0;
	uint8_t a = 0xFF;

	uint32_t as_rgba() { return (r << 24) | (g << 16) | (b << 8) | a; }
};
