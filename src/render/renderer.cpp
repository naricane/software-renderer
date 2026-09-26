#include "renderer.hpp"
#include "core/framebuffer.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

void
Renderer::set_target(Framebuffer* target)
{
	this->target = target;
}

void
Renderer::clear()
{
	if (!target) {
		return;
	}

	target->color_buffer.clear();
	target->z_buffer.clear(1.f);
}
