#pragma once

#include <SDL3/SDL_render.h>

struct Renderer {
  SDL_Renderer *sdl_renderer;
  SDL_Texture *framebuffer;

  Renderer(SDL_Window *window);
};
