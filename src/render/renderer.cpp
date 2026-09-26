#include "renderer.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

void
Renderer::clear()
{
	fb.color_buffer.clear();
	fb.z_buffer.clear(1.f);
}
