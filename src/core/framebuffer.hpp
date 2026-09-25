#pragma once
#include "core/data_types.hpp"

class Framebuffer
{
private:
	size_t buf_width;
	size_t buf_height;

public:
	ColorBuffer color_buffer;
	ZBuffer z_buffer;

	Framebuffer(size_t width, size_t height)
		: buf_width(width)
		, buf_height(height)
		, color_buffer(width, height)
		, z_buffer(width, height)
	{
	}

	size_t width() { return buf_width; }
	size_t height() { return buf_height; }
};
