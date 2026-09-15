#include "obj_loader.hpp"
#include <charconv>
#include <fstream>
#include <sstream>
#include <string>

namespace obj {

static inline unsigned int
parse_face_token(std::string_view token)
{
	std::size_t slash_pos = token.find("/");
	std::string_view digits;

	if (slash_pos != std::string::npos) {
		digits = token.substr(0, slash_pos).data();
	} else {
		digits = token.data();
	}

	unsigned int result;
	std::from_chars(digits.data(), digits.data() + digits.size(), result);

	return result;
}

void
load_mesh(
	std::string_view path,
	std::vector<Vertex>& mesh_vertices,
	std::vector<unsigned int>& mesh_indices
)
{
	std::ifstream file(path.data());

	if (!file) {
		return;
	}

	std::vector<Vec3> positions;
	std::vector<unsigned int> indices;

	std::string line;

	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v") {
			Vec3 pos;
			iss >> pos.x >> pos.y >> pos.z;
			positions.emplace_back(pos);
		} else if (prefix == "f") {
			std::vector<unsigned int> v_indices;
			std::string token;
			while (iss >> token) {
				v_indices.emplace_back(parse_face_token(token));
			}

			for (std::size_t i = 1; i + 1 < v_indices.size(); i++) {
				indices.push_back(v_indices[0] - 1);
				indices.push_back(v_indices[i] - 1);
				indices.push_back(v_indices[i + 1] - 1);
			}
		}
	}

	mesh_indices = indices;

	for (const auto& p : positions) {
		mesh_vertices.emplace_back(Vertex{ p, Color{ 255, 255, 255 } });
	}
}

}
