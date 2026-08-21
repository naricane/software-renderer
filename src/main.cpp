#include "constants.hpp"
#include "rasterize.hpp"
#include "renderer.hpp"
#include "sdl_deleters.hpp"
#include <SDL3/SDL.h>

int
main()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return 1;
	}

	sdl::window window(SDL_CreateWindow("Software Renderer", WIDTH, HEIGHT, 0));
	if (!window) {
		SDL_Log("CreateWindow failed: %s", SDL_GetError());
		return 1;
	}

	Renderer renderer;
	Framebuffer fb;
	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		fb.clear();
		for (int i = 0; i < WIDTH * HEIGHT; ++i) {
			rasterize::put_pixel(fb, Vec2i{ i % WIDTH, i / WIDTH }, 0x4287F5FF);
		}

		rasterize::plot_line(fb, Vec2i{ 100, 90 }, Vec2i{ 200, 100 });
		rasterize::plot_line(fb, Vec2i{ 200, 100 }, Vec2i{ 60, 200 });
		rasterize::plot_line(fb, Vec2i{ 60, 200 }, Vec2i{ 100, 90 });

		renderer.display(window.get(), fb);
	}

	return 0;
}
