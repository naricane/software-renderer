#pragma once

#include "math.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

struct Renderer {
  SDL_Surface *fb_surface;
  std::vector<uint32_t> fb_pixels;

  Renderer(SDL_Window *window);
  void put_pixel(Vec2i position, uint32_t color);
  void clear();
  void display(SDL_Window *window);
};
