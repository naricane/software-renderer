#include "renderer.hpp"
#include "constants.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>

Renderer::Renderer(SDL_Window *window) {
  sdl_renderer = SDL_CreateRenderer(window, nullptr);
  if (!sdl_renderer) {
    SDL_Log("CreateRenderer failed: %s", SDL_GetError());
    exit(1);
  }

  framebuffer = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  if (!framebuffer) {
    SDL_Log("CreateTexture failed: %s", SDL_GetError());
    exit(1);
  }
}
