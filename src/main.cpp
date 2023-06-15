#include "../dependencies/game.hpp"


 /**
 * main - Main function to the game.
 * @argc: Number of arguments.
 * @args: Arguments.
 * return: Return value of the function call to the main function.
 */

int main(int argc, char *args[])
{

    /* Player position and direccion */
	float plaX = 1.5, plaY = 8.5, dirX = 0.0, dirY = 1.0;

	bool run = true;
	int time, oldTime = 0, frameTime = 0;
	int mouseX, mouseY;
	float posX, posY;

    /* Initialize SDL*/
	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
			"SDL failed to initialize; %s\n",
			SDL_GetError());

	/* Create window */
	SDL_Window *window = SDL_CreateWindow("Game Maze", 100, 100, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN);
	ASSERT(window, "failed to create window\n", SDL_GetError());

	/* Create renderer window */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	ASSERT(renderer, "failed to create renderer\n", SDL_GetError());

    /* Create game objets */
	Game maze;
	maze.setRenderer(renderer, width, height);
	maze.setMapWalls("pics/walls.bmp", 32, 32);
	maze.setMapObjs("pics/objs.bmp", 64, 64, 160, 0, 128);
	maze.setMap(map, MAPWIDTH, MAPHEIGHT);
	maze.setMapObjs(map_objs, 30);
	maze.setCiel("pics/sky3.bmp");
	maze.setFlats(map_floor, map_ciel);
	maze.setLights(map_light);
	maze.setCam(plaX, plaY, dirX, dirY);
	maze.init(window);

	SDL_Event event;
	SDL_ShowCursor(SDL_DISABLE);

	while (run) {
		maze.show();
		frameTime = 0;

		/* Timing for input and FPS counter */
		while (frameTime < 1) {
			time = SDL_GetTicks();
			frameTime += time - oldTime;
			oldTime = time;
		}

		/* Frametime is the time this frame has taken, in seconds */
		frameTime = 1000 / frameTime;

		posX = 0;
		posY = 0;
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		float moveSpeed = 0.05;

		/* Move forward */
		if (keys[SDL_SCANCODE_W]) {
			posX += moveSpeed * cosf(dirX) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX) * 60.f / frameTime;
		}

		/* Move left */
		if (keys[SDL_SCANCODE_A]) {
			posX += moveSpeed * cosf(dirX - 1.57) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX - 1.57) * 60.f / frameTime;
		}

		/* Move right */
		if (keys[SDL_SCANCODE_D]) {
			posX += moveSpeed * cosf(dirX + 1.57) * 60.f / frameTime;
			posY += moveSpeed * sinf(dirX + 1.57) * 60.f / frameTime;
		}

		/* Move back */
		if (keys[SDL_SCANCODE_S]) {
			posX -= moveSpeed * cosf(dirX) * 60.f / frameTime;
			posY -= moveSpeed * sinf(dirX) * 60.f / frameTime;
		}

        /* Check for collicion with walls */
		if (!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
		!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
		!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + posX - .3)] &&
		!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + posX - .3)]) {
			plaX += posX;
			plaY += posY;
		}

		if (!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX + .3)] &&
			!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX + .3)] &&
			!map[(int)(plaY + posY + .3) * MAPWIDTH + (int)(plaX - .3)] &&
			!map[(int)(plaY + posY - .3) * MAPWIDTH + (int)(plaX - .3)]) {
				plaY += posY;
		}

		if (!map[(int)(plaY + .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
			!map[(int)(plaY - .3) * MAPWIDTH + (int)(plaX + posX + .3)] &&
			!map[(int)(plaY + .3) * MAPWIDTH + (int)(plaX + posX - .3)] &&
			!map[(int)(plaY - .3) * MAPWIDTH + (int)(plaX + posX - .3)]) {
				plaX += posX;
		}

		/* Turn the camera to left */
		if (keys[SDL_SCANCODE_LEFT]) {
            dirX -= moveSpeed * 60.f / frameTime / 2;
        }

		/* Turn the camera to right */
		if (keys[SDL_SCANCODE_RIGHT]) {
            dirX += moveSpeed * 60.f / frameTime / 2;
        }

		/* Event loop */
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
                run = false;
            }

            /* Checks if a key was pressed */
			if (event.type == SDL_KEYDOWN) {

                /* Checks if the Escape key was pressed */
				if (event.key.keysym.sym == SDLK_ESCAPE) {
                    run = false;
                }
			}
		}

		/* Retrieve the current state of the mouse. */
		SDL_GetMouseState(&mouseX, &mouseY);

		/* Mouse rotation velocity */
		dirX += (mouseX - width / 2) * 0.00070;

		/* Move the mouse to the given position in global screen space. */
		SDL_WarpMouseGlobal(width / 2, height / 2);

		/* Updates the screen with any rendering made in a previous call. */
		SDL_RenderPresent(renderer);

		/* Set camera position */
		maze.setCam(plaX, plaY, dirX, dirY);
	}

	/* Destroy rendering context for a window and free associated textures. */
	SDL_DestroyRenderer(renderer);

	/* Destroy a window. */
	SDL_DestroyWindow(window);

	return 0;
};
