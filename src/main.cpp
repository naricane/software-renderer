#include "constants.hpp"
#include "math.hpp"
#include "renderer.hpp"
#include "sdl_deleters.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_timer.h>
#include <algorithm>
#include <cmath>

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
	SDL_SetWindowRelativeMouseMode(window.get(), true);

	Renderer renderer;
	bool running = true;
	SDL_Event event;

	std::vector<Vertex> cube_vertices = {
		{ -0.5f, -0.5f, -0.5f }, { 0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, -0.5f },
		{ -0.5f, 0.5f, -0.5f },  { -0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },    { -0.5f, 0.5f, 0.5f },
	};

	std::vector<unsigned int> cube_indices = {
		0, 2, 1, 0, 3, 2, 4, 5, 6, 4, 6, 7, 0, 4, 7, 0, 7, 3,
		1, 2, 6, 1, 6, 5, 0, 1, 5, 0, 5, 4, 3, 7, 6, 3, 6, 2,
	};

	float angle = .0f;

	Vec3 up{ 0, 1, 0 };
	float fov_y = 3.14 / 3.f;
	float aspect = (float)WIDTH / HEIGHT;
	float near_z = .1f;
	float far_z = 100.f;

	Vec3 cam_pos{ 0, 0, 3.f };
	float cam_yaw = 3.14f;
	float cam_pitch = .0f;
	float move_speed = .05f;
	float look_speed = .003f;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				cam_yaw -= event.motion.xrel * look_speed;
				cam_pitch -= event.motion.yrel * look_speed;
			}
		}

		cam_pitch = std::clamp(cam_pitch, -1.55f, 1.55f);
		Vec3 forward{
			std::cos(cam_pitch) * std::sin(cam_yaw),
			std::sin(cam_pitch),
			std::cos(cam_pitch) * std::cos(cam_yaw),
		};
		forward = vector::normalize(forward);

		Vec3 right = vector::normalize(vector::cross(forward, up));

		const bool* keys = SDL_GetKeyboardState(nullptr);
		if (keys[SDL_SCANCODE_W]) {
			cam_pos = cam_pos + forward * move_speed;
		}
		if (keys[SDL_SCANCODE_S]) {
			cam_pos = cam_pos - forward * move_speed;
		}
		if (keys[SDL_SCANCODE_D]) {
			cam_pos = cam_pos + right * move_speed;
		}
		if (keys[SDL_SCANCODE_A]) {
			cam_pos = cam_pos - right * move_speed;
		}
		if (keys[SDL_SCANCODE_SPACE]) {
			cam_pos = cam_pos + up * move_speed;
		}
		if (keys[SDL_SCANCODE_LSHIFT]) {
			cam_pos = cam_pos - up * move_speed;
		}

		angle += 0.02f;
		Mat4 m = matrix::rotate_y(angle);
		Mat4 v = matrix::look_at(cam_pos, cam_pos + forward, up);
		Mat4 p = matrix::perspective(fov_y, aspect, near_z, far_z);

		Mat4 mvp = p * v * m;

		renderer.clear();
		renderer.draw_elements(cube_vertices, cube_indices, mvp);
		renderer.display(window.get());

		SDL_Delay(16);
	}

	return 0;
}
