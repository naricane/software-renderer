#include "renderer.hpp"
#include "constants.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>

Renderer::Renderer(SDL_Window *window) : fb_pixels(WIDTH * HEIGHT, 0x0) {
  fb_surface = SDL_GetWindowSurface(window);
  if (!fb_surface) {
    SDL_Log("GetWindowSurface failed: %s", SDL_GetError());
    exit(1);
  }
}

void Renderer::put_pixel(Vec2i position, uint32_t color) {
  if (position.x < 0 || position.x >= WIDTH || position.y < 0 ||
      position.y >= HEIGHT) {
    return;
  }
  fb_pixels[position.x + position.y * WIDTH] = color;
}

void Renderer::clear() {
  for (int i = 0; i < WIDTH * HEIGHT; ++i) {
    put_pixel(Vec2i{i % WIDTH, i / WIDTH}, 0x0);
  }
}
void Renderer::display(SDL_Window *window) {
  SDL_LockSurface(fb_surface);
  SDL_ConvertPixels(WIDTH, HEIGHT, SDL_PIXELFORMAT_RGBA8888, fb_pixels.data(),
                    WIDTH * sizeof(uint32_t), fb_surface->format,
                    fb_surface->pixels, fb_surface->pitch);
  SDL_UnlockSurface(fb_surface);

  SDL_UpdateWindowSurface(window);
}
