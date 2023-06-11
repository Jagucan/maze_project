#include "../dependencies/game.h"


 /**
 * main - Main function to the game.
 * @argc: Number of arguments.
 * @args: Arguments.
 * return: Return value of the function call to the main function.
 */

int main(int argc, char *args[])
{

	float plaX = 1.5, plaY = 8.5, dirX = 0.0, dirY = 1.0;
	bool run = true;
	int time, oldTime = 0, frameTime = 0;
	int mouseX, mouseY;
	float posX, posY;

	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
			"SDL failed to initialize; %s\n",
			SDL_GetError());

	/* create window */
	SDL_Window *window = SDL_CreateWindow("Game Maze", 100, 100, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN);
	ASSERT(window, "failed to create window\n", SDL_GetError());

	/* create renderer window */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	ASSERT(renderer, "failed to create renderer\n", SDL_GetError());

	Game maze;
	maze.setRenderer(renderer, width, height);
	maze.setMapWalls("pics/walls.bmp", 32, 32);
	maze.setMapObjs("pics/objs.bmp", 64, 64, 160, 0, 128);
	maze.setMap(map, MAPWIDTH, MAPHEIGHT);
	maze.setMapObjs(map_objs, 3);
	maze.setCiel("pics/sky_pingoo.bmp");
	maze.setFlats(map_floor, map_ciel);
	maze.setLights(map_light);
	maze.setCam(plaX, plaY, dirX, dirY);
	maze.init(window);

	SDL_Event event;
	SDL_ShowCursor(SDL_DISABLE);

	while (run)
	{

		maze.show();
		frameTime = 0;

		/* timing for input and FPS counter */
		while (frameTime < 1)
		{
			time = SDL_GetTicks();
			frameTime += time - oldTime;
			oldTime = time;
		}

		/* frametime is the time this frame has taken, in seconds */
		frameTime = 1000 / frameTime;
		posX = 0;
		posY = 0;
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		float moveSpeed = 0.05;

		/* move forward */
		if (keys[SDL_SCANCODE_W])
		{
			posX += moveSpeed * cosf(dirX) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX) * 60.f / frameTime;
		}

		/* move left */
		if (keys[SDL_SCANCODE_A])
		{
			posX += moveSpeed * cosf(dirX - 1.57) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX - 1.57) * 60.f / frameTime;
		}

		/* move right */
		if (keys[SDL_SCANCODE_D])
		{
			posX += moveSpeed * cosf(dirX + 1.57) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX + 1.57) * 60.f / frameTime;
		}

		/* move back */
		if (keys[SDL_SCANCODE_S])
		{
			posX -= moveSpeed * cosf(dirX) * 60.f / frameTime;
			posY -= moveSpeed * sinf(dirX) * 60.f / frameTime;
		}

		if \
		(!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
		!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
		!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + posX - .3)] &&
		!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + posX - .3)])
		{
			plaX += posX;
			plaY += posY;
		}

		if (!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + .3)] &&
			!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + .3)] &&
			!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX - .3)] &&
			!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX - .3)])
			{
				plaY += posY;
		}

		if (!map[(int)(plaY + .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
			!map[(int)(plaY - .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
			!map[(int)(plaY + .3) * MAPWIDTH + (int)(plaX + posX - .3)] &&
			!map[(int)(plaY - .3) * MAPWIDTH + (int)(plaX + posX - .3)])
			{
				plaX += posX;
		}

		/* turn the camera to left */
		if (keys[SDL_SCANCODE_LEFT])
			dirX -= moveSpeed * 60.f / frameTime / 2;

		/* turn the camera to right */
		if (keys[SDL_SCANCODE_RIGHT])
			dirX += moveSpeed * 60.f / frameTime / 2;

		/* event loop */
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run = false;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					run = false;
			}
		}

		/* Retrieve the current state of the mouse. */
		SDL_GetMouseState(&mouseX, &mouseY);

		/* mouse rotation velocity */
		dirX += (mouseX - width / 2) * 0.00070;

		/* Move the mouse to the given position in global screen space. */
		SDL_WarpMouseGlobal(width / 2, height / 2);

		/* Updates the screen with any rendering made in a previous call. */
		SDL_RenderPresent(renderer);

		/* set cam position */
		maze.setCam(plaX, plaY, dirX, dirY);
	}

	/* Destroy rendering context for a window and free associated textures. */
	SDL_DestroyRenderer(renderer);

	/* Destroy a window. */
	SDL_DestroyWindow(window);

	return 0;
};
