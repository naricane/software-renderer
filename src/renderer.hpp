#pragma once

#include "framebuffer.hpp"
#include <SDL3/SDL_render.h>

class Renderer
{
public:
	Renderer() {}
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = default;
	Renderer& operator=(Renderer&&) = default;

	void display(SDL_Window* window, Framebuffer& fb);
};
