#include "constants.hpp"
#include "renderer.hpp"
#include <SDL3/SDL.h>
#include <cmath>
#include <cstdlib>

/* cool explanation: https://www.youtube.com/watch?v=CceepU1vIKo */
void plot_line_h(Renderer &r, Vec2i from, Vec2i to) {
  if (from.x > to.x) {
    std::swap(from.x, to.x);
    std::swap(from.y, to.y);
  }

  Vec2i d = {to.x - from.x, to.y - from.y};

  int dir = d.y < 0 ? -1 : 1;
  d.y *= dir;

  if (d.x != 0) {
    int y = from.y;
    int p = 2 * d.y - d.x;

    for (int i = 0; i < d.x + 1; i++) {
      r.put_pixel({from.x + i, y}, LINE_COLOR);

      if (p >= 0) {
        y += dir;
        p = p - 2 * d.x;
      }
      p = p + 2 * d.y;
    }
  }
}

void plot_line_v(Renderer &r, Vec2i from, Vec2i to) {
  if (from.y > to.y) {
    std::swap(from.x, to.x);
    std::swap(from.y, to.y);
  }

  Vec2i d = {to.x - from.x, to.y - from.y};

  int dir = d.x < 0 ? -1 : 1;
  d.x *= dir;

  if (d.y != 0) {
    int x = from.x;
    int p = 2 * d.x - d.y;

    for (int i = 0; i < d.y + 1; i++) {
      r.put_pixel({x, from.y + i}, LINE_COLOR);

      if (p >= 0) {
        x += dir;
        p = p - 2 * d.y;
      }
      p = p + 2 * d.x;
    }
  }
}

void plot_line(Renderer &r, Vec2i from, Vec2i to) {
  if (std::abs(to.x - from.x) > std::abs(to.y - from.y)) {
    plot_line_h(r, from, to);
  } else {
    plot_line_v(r, from, to);
  }
}

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

  Renderer renderer;
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

    plot_line(renderer, Vec2i{100, 90}, Vec2i{200, 100});
    plot_line(renderer, Vec2i{200, 100}, Vec2i{60, 200});
    plot_line(renderer, Vec2i{60, 200}, Vec2i{100, 90});

    renderer.display(window);
  }

  return 0;
}
