#pragma once

#include "core/vertex.hpp"
#include <string_view>
#include <vector>

namespace obj {

void
load_mesh(
	std::string_view path,
	std::vector<Vertex>& mesh_vertices,
	std::vector<unsigned int>& mesh_indices
);

}
