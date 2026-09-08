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

	void clear(T value = T{}) { std::fill(data.begin(), data.end(), value); }
	std::span<T> get_span() { return std::span{ data }; }
};
