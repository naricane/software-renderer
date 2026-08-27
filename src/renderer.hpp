#pragma once

#include "framebuffer.hpp"
#include "vertex.hpp"
#include <SDL3/SDL_render.h>

class Renderer
{
private:
	Framebuffer fb;

public:
	Renderer() {}
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	Renderer(Renderer&&) = default;
	Renderer& operator=(Renderer&&) = default;

	void draw_elements(std::span<const Vertex> verts, std::span<const unsigned int> idx, Mat4 mvp);
	void clear();
	void display(SDL_Window* window);
};
