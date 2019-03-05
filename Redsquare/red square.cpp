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

	int left = 1;
	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 50;
	rectangle.h = 50;

	// frame loop
	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);


		if (rectangle.x > 640)
		{
			left = 0;
		}
		else if (rectangle.x < 0)
		{
			left = 1;
		}

		if (left)
			rectangle.x++;
		else
			rectangle.x--;
		SDL_RenderFillRect(renderer, &rectangle);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}