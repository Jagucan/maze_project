#include "../dependencies/game.h"


 /**
 * main - Main function to the game.
 * @argc: Number of arguments.
 * @args: Arguments.
 * return: Return value of the function call to the main function.
 */

int main(int argc, char *args[]) {

	float px = 1.5, py = 8.5, pa = 0.0, pf = 1.0;
	float speed = 0.05;
	bool run = true;
	int stt, ett = 0, dtt = 0, ctt;
	const Uint8* keys;
	int mousex, mousey;
	float xm, ym;

	ASSERT(!SDL_Init(SDL_INIT_VIDEO),
		   "SDL failed to initialize; %s\n",
		   SDL_GetError());

	// create window
	SDL_Window *window = SDL_CreateWindow("Game Maze", 100, 100, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN);
	ASSERT(window, "failed to create window\n", SDL_GetError());

	//create renderer window
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	ASSERT(renderer, "failed to create renderer\n", SDL_GetError());

	Game maze;
	maze.setRenderer(renderer, width, height);
	maze.setTileWalls("pics/walls.bmp", 32, 32);
	maze.setTileObjs("pics/objs.bmp", 64, 64, 160, 0, 128);
	maze.setMap(map, mapWidth, mapHeight);
	maze.setMapObjs(map_objs, 3);
	maze.setSky("pics/sky.bmp");
	maze.setFlats(map_floor, map_ciel);
	maze.setLights(map_light);
	maze.setCam(px, py, pa, pf);
	maze.init(window);

	SDL_Event event;
	SDL_ShowCursor(SDL_DISABLE);

	while (run) {

		maze.show();
		dtt = 0;

		while (dtt < 1) {
			stt = SDL_GetTicks();
			dtt += stt - ett;
			ett = stt;
		}

		ctt = 0;
		dtt = 1000 / dtt;
		xm = 0;
		ym = 0;
		keys = SDL_GetKeyboardState(NULL);

		// move forward
		if (keys[SDL_SCANCODE_W]) {
			xm += speed * cosf(pa) * 60.f / dtt;
			ym += speed * sinf(pa) * 60.f / dtt;
		}

		// move left
		if (keys[SDL_SCANCODE_A]) {
			xm += speed * cosf(pa - 1.57) * 60.f / dtt;
			ym += speed * sinf(pa - 1.57) * 60.f / dtt;
		}

		// move right
		if (keys[SDL_SCANCODE_D]) {
			xm += speed * cosf(pa + 1.57) * 60.f / dtt;
			ym += speed * sinf(pa + 1.57) * 60.f / dtt;
		}

		// move back
		if (keys[SDL_SCANCODE_S]) {
			xm -= speed * cosf(pa) * 60.f / dtt;
			ym -= speed * sinf(pa) * 60.f / dtt;
		}

		if (!map[(int)(py + ym + .3) * mapWidth + (int)(px + xm + .3)] &&
			!map[(int)(py + ym - .3) * mapWidth + (int)(px + xm + .3)] &&
			!map[(int)(py + ym + .3) * mapWidth + (int)(px + xm - .3)] &&
			!map[(int)(py + ym - .3) * mapWidth + (int)(px + xm - .3)]) {
			px += xm;
			py += ym;
		}

		if (!map[(int)(py + ym + .3) * mapWidth + (int)(px + .3)] &&
			!map[(int)(py + ym - .3) * mapWidth + (int)(px + .3)] &&
			!map[(int)(py + ym + .3) * mapWidth + (int)(px - .3)] &&
			!map[(int)(py + ym - .3) * mapWidth + (int)(px - .3)]) {
			py += ym;
		}

		if (!map[(int)(py + .3) * mapWidth + (int)(px + xm + .3)] &&
			!map[(int)(py - .3) * mapWidth + (int)(px + xm + .3)] &&
			!map[(int)(py + .3) * mapWidth + (int)(px + xm - .3)] &&
			!map[(int)(py - .3) * mapWidth + (int)(px + xm - .3)]) {
			px += xm;
		}

		// turn the camera to left
		if (keys[SDL_SCANCODE_LEFT])
			pa -= speed * 60.f / dtt / 2;

		// turn the camera to right
		if (keys[SDL_SCANCODE_RIGHT])
			pa += speed * 60.f / dtt / 2;

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT)
				run = false;

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					run = false;
			}

		}

		SDL_GetMouseState(&mousex, &mousey);

		// mouse rotation velocity
		pa += (mousex - width / 2) * 0.0001;

		//
		SDL_WarpMouseGlobal(width / 2, height / 2);

		//
		SDL_RenderPresent(renderer);

		//
		maze.setCam(px, py, pa, pf);
	}

	// destroy renderer
	SDL_DestroyRenderer(renderer);

	// destroy window
	SDL_DestroyWindow(window);

	return 0;
};
