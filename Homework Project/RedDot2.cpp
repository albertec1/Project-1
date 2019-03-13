#include <stdio.h>
#include <iostream>
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment(lib, "SDL/SDL2main.lib")
#pragma comment(lib, "SDL/SDL2.lib")
#pragma comment(lib, "SDL_Image/SDL2_image.lib")
#pragma comment(lib, "SDL_mixer/SDL2_mixer.lib")


int main(int argc, char *argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, 0);

	if (window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int Initialized = IMG_Init(flags);

	/*Initialized&flags is a bitwise(and) operation between "Initialized", which is equal to IMG_Init(flags), and "flags" which is equal toIMG_INIT_PNG|IMG_INIT_JPG.
	Since IMG_Init(flags) is just initializing the IMG_INIT_PNG and _JPG, a mask of flags of initialized should equal the actual "flags".*/

	if ((Initialized&flags) != flags)
	{
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
		// handle error

	}


	// load support for the OGG sample/music formats
	int MIX_Flags = MIX_INIT_OGG;
	int initted = Mix_Init(MIX_Flags);
	if (initted&MIX_Flags != MIX_Flags)
	{
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		// handle error
	}
	

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}


	Mix_Chunk *effect = Mix_LoadWAV("music/efect.wav");
	if (!effect)
	{
		printf("Mix_LoadWAV: %s\n", Mix_GetError());
		// handle error
	}

	Mix_Music *music = Mix_LoadMUS("music/background.ogg");
	if (!music)
	{
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// this might be a critical error...
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

	
	if (Mix_PlayMusic(music, -1) == -1)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
	// frame loop
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (state[SDL_SCANCODE_ESCAPE])
			{
				quit = true;
			}
			if (state[SDL_SCANCODE_W])
			{
				rectangle.y--;
				if (laserCharged)
				{
					laser.y--;
				}
			}
			if (state[SDL_SCANCODE_A])
			{
				rectangle.x--;
				if (laserCharged)
				{
					laser.x--;
				}
			}
			if (state[SDL_SCANCODE_S])
			{
				rectangle.y++;
				if (laserCharged)
				{
					laser.y++;
				}
			}
			if (state[SDL_SCANCODE_D])
			{
				rectangle.x++;
				if (laserCharged)
				{
					laser.x++;
				}
			}
			if (state[SDL_SCANCODE_SPACE])
			{
				laserCharged = false;
				Mix_PlayChannel(-1, effect, 0);
				
			}
		}
		if (!laserCharged)
		{
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

	Mix_FreeChunk(effect);
	effect = NULL; // to be safe...

	Mix_FreeMusic(music);
	music = NULL; // so we know we freed it...

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}
