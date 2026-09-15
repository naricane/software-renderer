#pragma once

#include "core/data_types.hpp"
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
	FrameBuffer fb;
	ZBuffer zb;

public:
	Renderer() {}
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
			Out o0 = sh.vertex(vertices[indices[i]]);
			Out o1 = sh.vertex(vertices[indices[i + 1]]);
			Out o2 = sh.vertex(vertices[indices[i + 2]]);

			constexpr float near_z = 0.1f;

			if (o0.position.w <= near_z || o1.position.w <= near_z || o2.position.w <= near_z) {
				continue;
			}

			rasterize::fill_triangle(
				sh,
				fb,
				zb,
				to_screen(o0.clip_pos, Vec2i{ WIDTH, HEIGHT }),
				to_screen(o1.clip_pos, Vec2i{ WIDTH, HEIGHT }),
				to_screen(o2.clip_pos, Vec2i{ WIDTH, HEIGHT }),
				o0.clip_pos.z / o0.clip_pos.w,
				o1.clip_pos.z / o1.clip_pos.w,
				o2.clip_pos.z / o2.clip_pos.w,
				o0,
				o1,
				o2
			);
		}
	}
	void clear();
	void display(SDL_Window* window);
};
