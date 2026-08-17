#include "renderer.hpp"
#include "constants.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>

Renderer::Renderer(SDL_Window *window) : pixels(WIDTH * HEIGHT, 0x0) {
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

void Renderer::put_pixel(Vec2i position, uint32_t color) {
  if (position.x < 0 || position.x >= WIDTH || position.y < 0 ||
      position.y >= HEIGHT) {
    return;
  }
  pixels[position.x + position.y * WIDTH] = color;
}

void Renderer::clear() {
  SDL_RenderClear(sdl_renderer);
  for (int i = 0; i < WIDTH * HEIGHT; ++i) {
    put_pixel(Vec2i{i % WIDTH, i / WIDTH}, 0x0);
  }
}
void Renderer::display() {
  SDL_UpdateTexture(framebuffer, nullptr, pixels.data(),
                    WIDTH * sizeof(uint32_t));
  SDL_RenderTexture(sdl_renderer, framebuffer, nullptr, nullptr);
  SDL_RenderPresent(sdl_renderer);
}
