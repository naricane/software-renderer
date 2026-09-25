#include "renderer.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

void
Renderer::clear()
{
	cb.clear();
	zb.clear(1.f);
}
