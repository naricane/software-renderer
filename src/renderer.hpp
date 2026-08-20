#pragma once

#include "math.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

class Renderer {
private:
  std::vector<uint32_t> fb_pixels;

public:
  Renderer();

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  Renderer(Renderer &&) = default;
  Renderer &operator=(Renderer &&) = default;

  void put_pixel(Vec2i position, uint32_t color);
  void clear();
  void display(SDL_Window *window);
};
