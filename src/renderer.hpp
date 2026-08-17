#pragma once

#include "math.hpp"
#include <SDL3/SDL_render.h>
#include <vector>

struct Renderer {
  SDL_Renderer *sdl_renderer;
  SDL_Texture *framebuffer;
  std::vector<uint32_t> pixels;

  Renderer(SDL_Window *window);
  void put_pixel(Vec2i position, uint32_t color);
  void clear();
  void display();
};
