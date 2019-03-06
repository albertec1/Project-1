#include <iostream>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL/SDL2main.lib")
#pragma comment(lib, "SDL/SDL2.lib")


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, 0);

	if (window == NULL) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL) {
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	bool quit = false;
	//Struct (Event handler)
	SDL_Event event;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	

	int left = 1;
	SDL_Rect rectangle;
	rectangle.x = 240;
	rectangle.y = 240;
	rectangle.w = 50;
	rectangle.h = 50;

	bool laserCharged = true;

	SDL_Rect laser;
	laser.x = 253;
	laser.y = 260;
	laser.w = 25;
	laser.h = 5;
	

	// frame loop
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (state[SDL_SCANCODE_W]) {
				rectangle.y--;
				if (laserCharged)
				{
					laser.y--;
				}
			}
			if (state[SDL_SCANCODE_A]) {
				rectangle.x--;
				if (laserCharged)
				{
					laser.x--;
				}
			}
			if (state[SDL_SCANCODE_S]) {
				rectangle.y++;
				if (laserCharged)
				{
					laser.y++;
				}
			}
			if (state[SDL_SCANCODE_D]) {
				rectangle.x++;
				if (laserCharged)
				{
					laser.x++;
				}
			}
			if (state[SDL_SCANCODE_SPACE]) {
				laserCharged = false;
			}
		}
		if (!laserCharged) {
			laser.x++;
		}

		if (laser.x > 500)
		{
			laser.x = rectangle.x + 13;
			laser.y = rectangle.y + 20;
			laserCharged = true;
		}

		//render background
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		//render rectangle & laser
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		SDL_RenderFillRect(renderer, &laser);
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle);

		SDL_RenderPresent(renderer);
		
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}