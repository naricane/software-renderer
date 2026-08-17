#include "constants.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Software Renderer", WIDTH, HEIGHT, 0);
  if (!window) {
    SDL_Log("CreateWindow failed: %s", SDL_GetError());
    return 1;
  }

  Renderer renderer(window);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    renderer.clear();
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
      renderer.put_pixel(Vec2i{i % WIDTH, i / WIDTH}, 0x4287F5FF);
    }
    renderer.display();
  }

  return 0;
}
