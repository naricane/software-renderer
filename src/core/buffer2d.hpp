#pragma once

#include "constants.hpp"
#include <span>
#include <vector>

template<typename T>
class Buffer2D
{
private:
	std::vector<T> data;

public:
	Buffer2D()
		: data(WIDTH * HEIGHT, T{})
	{
	}
	Buffer2D(const Buffer2D&) = delete;
	Buffer2D& operator=(const Buffer2D&) = delete;
	Buffer2D(Buffer2D&&) = default;
	Buffer2D& operator=(Buffer2D&&) = default;

	void clear(T value = T{}) { std::fill(data.begin(), data.end(), value); }
	std::span<T> get_span() { return std::span{ data }; }
};
