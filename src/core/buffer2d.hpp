#pragma once

#include "constants.hpp"
#include <span>
#include <vector>

template<typename T>
class Buffer2D
{
private:
	std::vector<T> data;
	size_t buf_width;
	size_t buf_height;

public:
	Buffer2D(size_t width, size_t height)
		: buf_width(width)
		, buf_height(height)
		, data(width * height, T{})
	{
	}
	Buffer2D(const Buffer2D&) = delete;
	Buffer2D& operator=(const Buffer2D&) = delete;
	Buffer2D(Buffer2D&&) = default;
	Buffer2D& operator=(Buffer2D&&) = default;

	size_t width() const { return buf_width; }
	size_t height() const { return buf_height; }

	void clear(T value = T{}) { std::fill(data.begin(), data.end(), value); }

	std::span<T> get_span() { return std::span{ data }; }
	T& at(size_t x, size_t y) { return data[y * buf_width + x]; }
	const T& at(size_t x, size_t y) const { return data[y * buf_width + x]; }
};
