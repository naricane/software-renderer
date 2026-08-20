#pragma once

#include "framebuffer.hpp"
#include "math.hpp"
#include <SDL3/SDL_render.h>

class Renderer {
private:
  Framebuffer framebuffer;

public:
  Renderer() {}
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&) = default;
  Renderer &operator=(Renderer &&) = default;

  void put_pixel(Vec2i position, uint32_t color);
  void clear();
  void display(SDL_Window *window);
};
