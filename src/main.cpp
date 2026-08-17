#include <SDL3/SDL.h>
#include <cstdint>
#include <vector>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

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

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    SDL_Log("CreateRenderer failed: %s", SDL_GetError());
    return 1;
  }

  SDL_Texture *framebuffer =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
  if (!framebuffer) {
    SDL_Log("CreateTexture failed: %s", SDL_GetError());
    return 1;
  }

  std::vector<uint32_t> pixels(WIDTH * HEIGHT, 0x0);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
      pixels[i] = 0x4287f5FF;
    }

    SDL_UpdateTexture(framebuffer, nullptr, pixels.data(),
                      WIDTH * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, framebuffer, nullptr, nullptr);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(framebuffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
