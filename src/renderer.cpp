#include "renderer.hpp"
#include "constants.hpp"
#include "rasterize.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

Vec2i
to_screen(const Vec4& clip, Vec2i screen_size)
{
	float ndc_x = clip.x / clip.w;
	float ndc_y = clip.y / clip.w;

	int sx = (int)((ndc_x + 1.f) * .5f * screen_size.x);
	int sy = (int)((1.f - ndc_y) * .5f * screen_size.y);

	return Vec2i{ sx, sy };
}

// temporary test
static uint32_t colors[] = {
	0x5EFBD1FF, 0xC07A8CFF, 0xE34FF4FF, 0xBFB932FF, 0x28DBDAFF, 0xAE3852FF,
};

void
Renderer::draw_elements(std::span<const Vertex> verts, std::span<const unsigned int> idx, Mat4 mvp)
{

	for (std::size_t i = 0; i + 2 < idx.size(); i += 3) {
		Vertex p0 = verts[idx[i]];
		Vertex p1 = verts[idx[i + 1]];
		Vertex p2 = verts[idx[i + 2]];

		Vec4 c0 = mvp * Vec4{ p0.position.x, p0.position.y, p0.position.z, 1.f };
		Vec4 c1 = mvp * Vec4{ p1.position.x, p1.position.y, p1.position.z, 1.f };
		Vec4 c2 = mvp * Vec4{ p2.position.x, p2.position.y, p2.position.z, 1.f };

		float near_z = .1f;
		if (c0.w <= near_z || c1.w <= near_z || c2.w <= near_z) {
			continue;
		}

		Vec2i a = to_screen(c0, Vec2i{ WIDTH, HEIGHT });
		Vec2i b = to_screen(c1, Vec2i{ WIDTH, HEIGHT });
		Vec2i c = to_screen(c2, Vec2i{ WIDTH, HEIGHT });
		rasterize::fill_triangle(fb, a, b, c, colors[(i / 6) % 6]);
	}
}

void
Renderer::clear()
{
	fb.clear();
}

void
Renderer::display(SDL_Window* window)
{
	SDL_Surface* fb_surface = SDL_GetWindowSurface(window);
	if (!fb_surface) {
		SDL_Log("GetWindowSurface failed: %s", SDL_GetError());
		return;
	}

	SDL_LockSurface(fb_surface);
	SDL_ConvertPixels(
		WIDTH,
		HEIGHT,
		SDL_PIXELFORMAT_RGBA8888,
		fb.get_pixels().data(),
		WIDTH * sizeof(uint32_t),
		fb_surface->format,
		fb_surface->pixels,
		fb_surface->pitch
	);
	SDL_UnlockSurface(fb_surface);

	SDL_UpdateWindowSurface(window);
}
