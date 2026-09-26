#pragma once

#include "core/constants.hpp"
#include "core/data_types.hpp"
#include "core/framebuffer.hpp"
#include "core/vertex.hpp"
#include "render/rasterize.hpp"
#include <SDL3/SDL_render.h>

inline Vec2i
to_screen(const Vec4& clip, Vec2i screen_size)
{
	float ndc_x = clip.x / clip.w;
	float ndc_y = clip.y / clip.w;

	int sx = (int)((ndc_x + 1.f) * .5f * screen_size.x);
	int sy = (int)((1.f - ndc_y) * .5f * screen_size.y);

	return Vec2i{ sx, sy };
}

class Renderer
{
private:
	Framebuffer fb;

public:
	Renderer()
		: fb(WIDTH, HEIGHT)
	{
	}
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = default;
	Renderer& operator=(Renderer&&) = default;

	template<typename Shader>
	void draw_elements(
		const Shader& sh,
		std::span<const Vertex> vertices,
		std::span<const unsigned int> indices
	)
	{
		using Out = typename Shader::Output;

		for (std::size_t i = 0; i + 2 < indices.size(); i += 3) {
			Out out_a = sh.vertex(vertices[indices[i]]);
			Out out_b = sh.vertex(vertices[indices[i + 1]]);
			Out out_c = sh.vertex(vertices[indices[i + 2]]);

			constexpr float near_z = 0.1f;

			if (out_a.position.w <= near_z || out_b.position.w <= near_z
				|| out_c.position.w <= near_z) {
				continue;
			}

			float depth_a = out_a.position.z / out_a.position.w;
			float depth_b = out_b.position.z / out_b.position.w;
			float depth_c = out_c.position.z / out_c.position.w;

			rasterize::fill_triangle(
				to_screen(out_a.position, Vec2i{ WIDTH, HEIGHT }),
				to_screen(out_b.position, Vec2i{ WIDTH, HEIGHT }),
				to_screen(out_c.position, Vec2i{ WIDTH, HEIGHT }),
				[&](int x, int y, float weight_a, float weight_b, float weight_c) {
					float depth = depth_a * weight_a + depth_b * weight_b + depth_c * weight_c;

					float& zb_cell = fb.z_buffer.get(x, y);
					if (depth >= zb_cell) {
						return;
					}
					zb_cell = depth;

					fb.color_buffer.get(x, y)
						= sh.fragment(out_a, out_b, out_c, weight_a, weight_b, weight_c);
				}
			);
		}
	}
	void clear();
};
