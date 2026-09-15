#include "renderer.hpp"
#include "core/constants.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

void
Renderer::clear()
{
	fb.clear();
	zb.clear(1.f);
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
		SDL_PIXELFORMAT_RGBA32,
		fb.get_span().data(),
		WIDTH * sizeof(uint32_t),
		fb_surface->format,
		fb_surface->pixels,
		fb_surface->pitch
	);
	SDL_UnlockSurface(fb_surface);

	SDL_UpdateWindowSurface(window);
}
