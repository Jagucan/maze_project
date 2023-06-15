#ifndef _GAME_HPP_
#define _GAME_HPP_


#include "main.hpp"


class Game {

private:

	float _sax, _say, _fs, slice, _d_del, _w_del, far, xfar, yfar, cos,
		sin, cut, xdel, ydel, steps, angle, sprite, x, y, sfar, sdir;

	int xobj, yobj, xdir, ydir, col, wallNumL, wallNumT, obj, xx, yy, xy, yx,
		cheight, dop, ssize, shor, sver, mapFloor, ceil_tile, pitch = 0,
		width, height, mapWidth, mapHeight, mapWallW,
		mapWallH, mapWallWw, mapWallWh, mapObjsW, mapObjsH,
		mapObjsWw, mapObjsWh, colorR, colorG, colorB,
		renderDataSize = 0, objMapSize, renderMax, halfHeight;

	Uint8 _fcr, _fcg, _fcb;

	Uint32 colorConv, ceilColor;

	SDL_Renderer *renderer;

	SDL_Surface *wallSurf, *cielSurf, *objSurf;

	SDL_Texture *textures, *walls, *Objs;

	Uint32 *pixBuffer = nullptr;

	Uint8 **RGBwallSurf, **RGBobjSurf;

	const char *mapWalls, *mapObjs, *mapCiel;

	int *map, *flatFloor, *flatCiel;

	float *mapLight, *renderDataMem = {};

	float **renderData, **objMap;

	float camX, camY, camA, camB, bright;


public:

	/**
	 * setRenderer - Set the game renderer and configure its dimensions.
	 * @param sRenderer: Reference to the SDL_Renderer pointer to be assigned.
	 * @param sWidth: The width of the game renderer.
	 * @param sHeight: The height of the game renderer.
	*/
	void setRenderer(SDL_Renderer*& sRenderer, int sWidth, int sHeight) {
		renderer = sRenderer;
		width = sWidth;
		height = sHeight;
		halfHeight = height / 2;
	};

	/**
	 * setMap - Configure the game map and set its dimensions.
	 * @param sMap: Pointer to the map data to be assigned to the Game class.
	 * @param sMapWidth: Width of the game map.
	 * @param sMapHeight: Height of the game map.
	*/
	void setMap(int *sMap, int sMapWidth, int sMapHeight) {
		map = sMap;
		mapWidth = sMapWidth;
		mapHeight = sMapHeight;
	};

	/**
	 * setMapObjs - Set the object map data and its size.
	 * @param sObjMap: Two-dimensional array containing the object map data.
	 *                  Each row represents an object and contains three elements: x, y, z coordinates.
	 * @param size: The number of objects in the object map.
	*/
	void setMapObjs(float sObjMap[MAPWIDTH][MAPHEIGHT], int size) {
		renderDataSize += size;
		objMapSize = size;
		objMap = new float* [size];
		for (int i = 0; i < size; i++)
			objMap[i] = sObjMap[i];
	};

	/**
	 * setFlats - Set the flat floor and ceil data.
	 * @param sFlatFloor: Array containing the flat floor data.
	 * @param sFlatCiel: Array containing the flat ceil data.
	*/
	void setFlats(int *sFlatFloor, int *sFlatCiel) {
		flatFloor = sFlatFloor;
		flatCiel = sFlatCiel;
	};

	/**
	 * setLights - Set the light data for the map.
	 * @param sLight: Array containing the light data for the map.
	*/
	void setLights(float *sLight) {
		mapLight = sLight;
	};

	/**
	 * setCiel - Set the skybox texture for the map.
	 * @param sCiel: Path to the skybox texture file.
	*/
	void setCiel(const char *sCiel) {
		mapCiel = sCiel;
	};

	/**
	 * setMapWalls - Set the wall texture map for the game.
	 * @param sMapWalls: Path to the wall texture map file.
	 * @param sMapWallW: Width of the wall texture map.
	 * @param sMapWallH: Height of the wall texture map.
	*/
	void setMapWalls(const char *sMapWalls, int sMapWallW, int sMapWallH) {
		mapWalls = sMapWalls;
		mapWallW = sMapWallW;
		mapWallH = sMapWallH;
	};

	/**
	 * setMapObjs - Set the game's object map and its properties.
	 * @param sMapObjs: Path to the object map file.
	 * @param sMapObjsW: Width of the object map.
	 * @param sMapObjsH: Height of the object map.
	 * @param sColorR: Value of the red component of the object color.
	 * @param sColorG: Value of the green component of the object color.
	 * @param sColorB: Value of the blue component of the object color.
	*/
	void setMapObjs(const char *sMapObjs, int sMapObjsW, int sMapObjsH, int sColorR, int sColorG, int sColorB) {
		mapObjs = sMapObjs;
		mapObjsW = sMapObjsW;
		mapObjsH = sMapObjsH;
		colorR = sColorR;
		colorG = sColorG;
		colorB = sColorB;
	};

	/**
	 * setCam - Set the camera position and orientation.
	 * @param scamX: X-coordinate of the camera position.
	 * @param scamY: Y-coordinate of the camera position.
	 * @param sCamA: Camera's initial angle.
	 * @param sCamB: Camera's initial pitch angle.
	*/
	void setCam(float scamX, float scamY, float sCamA, float sCamB) {
		camX = scamX;
		camY = scamY;
		camA = sCamA;
		camB = sCamB;
		while (camA > 3.14) camA -= 6.28;
		while (camA < -3.14) camA += 6.28;
	};

	/**
	 * init - Initialize the game renderer and load necessary resources.
	 * @param window: SDL_Window pointer to the game window.
	*/
	void init(SDL_Window *window) {
		const SDL_PixelFormat* sFrmt = SDL_GetWindowSurface(window)->format;
		Uint32 sFrmtG = SDL_GetWindowPixelFormat(window);
		renderDataSize += width;
		steps = camB / width;

		SDL_Surface *image = SDL_LoadBMP(mapWalls);
		wallSurf = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGB888, 0);
		walls = SDL_CreateTextureFromSurface(renderer, wallSurf);
		mapWallWw = image->w / mapWallW;
		mapWallWh = image->h / mapWallH;

		RGBwallSurf = new Uint8 * [wallSurf->w * wallSurf->h];
		for (int i = 0; i < wallSurf->w * wallSurf->h; i++) {
			SDL_GetRGB(getpixel(wallSurf, i % wallSurf->w, i / wallSurf->w), wallSurf->format, &_fcr, &_fcg, &_fcb);
			RGBwallSurf[i] = new Uint8[3];
		}
		for (int i = 0; i < wallSurf->w * wallSurf->h; i++) {
			SDL_GetRGB(getpixel(wallSurf, i % wallSurf->w, i / wallSurf->w), wallSurf->format, &_fcr, &_fcg, &_fcb);
			RGBwallSurf[i][0] = _fcr;
			RGBwallSurf[i][1] = _fcg;
			RGBwallSurf[i][2] = _fcb;
		}

		image = SDL_LoadBMP(mapObjs);
		objSurf = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGB888, 0);
		mapObjsWw = image->w / mapObjsW;
		mapObjsWh = image->h / mapObjsH;

		RGBobjSurf = new Uint8 * [objSurf->w * objSurf->h];
		for (int i = 0; i < objSurf->w * objSurf->h; i++) {
			SDL_GetRGB(getpixel(objSurf, i % objSurf->w, i / objSurf->w), objSurf->format, &_fcr, &_fcg, &_fcb);
			RGBobjSurf[i] = new Uint8[3];
		}
		for (int i = 0; i < objSurf->w * objSurf->h; i++) {
			SDL_GetRGB(getpixel(objSurf, i % objSurf->w, i / objSurf->w), objSurf->format, &_fcr, &_fcg, &_fcb);
			RGBobjSurf[i][0] = _fcr;
			RGBobjSurf[i][1] = _fcg;
			RGBobjSurf[i][2] = _fcb;
		}

		SDL_FreeSurface(image);

		image = SDL_LoadBMP(mapCiel);
		image = SDL_ConvertSurfaceFormat(image, sFrmtG, 0);
		cielSurf = image;

		renderData = new float* [renderDataSize];
		for (int i = 0; i < renderDataSize; i++) {
			renderData[i] = new float[7];
		}

		textures = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
		_d_del = 1.f / height;
		_w_del = 1.f / width;

		colorConv = RGB(colorR, colorG, colorB);
	};

	/**
	 * renderWalls - Render the walls of the game scene using raycasting.
	 */
	void renderWalls() {
		col = 0;
		for (angle = camA - camB / 2; angle < camA + camB / 2; angle += steps) {
			cos = cosf(angle);
			sin = sinf(angle);
			xdir = cos > 0;
			ydir = sin > 0;

			/* y iteration */
			if (sin) {
				ydel = camY - (int)camY;
				yy = 0;

				/* down */
				if (ydir) {
					while (!yobj) {
						yy += 1;
						yfar = (yy - ydel) / sin;
						yx = camX + yfar * cos;
						if (yy + camY >= mapHeight || yy + camY < 0 || yx >= mapWidth || yx < 0) {
							yfar = 100.0;
							break;
						}
						yobj = map[(int)(yy + camY) * mapWidth + yx];
					}
				}

				/* up */
				else {
					while (!yobj) {
						yfar = (yy - ydel) / sin;
						yy -= 1;
						yx = camX + yfar * cos;
						if (yy + camY >= mapHeight || yy + camY < 0 || yx >= mapWidth || yx < 0) {
							yfar = 100.0;
							break;
						}
						yobj = map[(int)(yy + camY) * mapWidth + yx];
					}
				}
			}

			else {
				yfar = 100.0;
			}
				
			/* x iteration */
			if (cos) {
				xdel = camX - (int)camX;
				xx = 0;

				/* right */
				if (xdir) {
					while (!xobj) {
						xx += 1;
						xfar = (xx - xdel) / cos;
						xy = camY + xfar * sin;
						if (xx + camX >= mapWidth || xx + camX < 0 || xy >= mapHeight || xy < 0)
						{
							xfar = 100.0;
							break;
						}
						xobj = map[xy * mapWidth + (int)(xx + camX)];
					}
				}
					
				/* left */
				else {
					while (!xobj) {
						xfar = (xx - xdel) / cos;
						xx -= 1;
						xy = camY + xfar * sin;
						if (xx + camX >= mapWidth || xx + camX < 0 || xy >= mapHeight || xy < 0)
						{
							xfar = 100.0;
							break;
						}
						xobj = map[xy * mapWidth + (int)(xx + camX)];
					}
				}
					
			}
			else {
				xfar = 100.0;
			}

			bright = 1;

			if (xfar < yfar) {
				obj = xobj;
				far = xfar;
				if (xx > 0) {
					cut = camY + sin * far - xy;
					bright = mapLight[(int)camX + xx + mapWidth * (int)xy - 1];
				}
				else {
					cut = 1 - camY - sin * far + xy;
					bright = mapLight[(int)camX + xx + mapWidth * (int)xy + 1];
				}
			}
			else {
				obj = yobj;
				far = yfar;
				if (yy < 0) {
					cut = camX + cos * far - yx;
					bright = mapLight[mapWidth * (int)camY + (int)yx + mapWidth * yy + mapWidth];
				}
				else {
					cut = 1 - camX - cos * far + yx;
					bright = mapLight[mapWidth * (int)camY + (int)yx + mapWidth * yy - mapWidth];
				}
			}

			if (obj) {
				renderData[col][0] = 0;
				renderData[col][1] = far;
				renderData[col][2] = (float)obj;
				renderData[col][3] = angle;
				renderData[col][4] = col;
				renderData[col][5] = cut;
				renderData[col][6] = bright;
				obj = 0;
			}

			else {
				renderData[col][0] = -1;
			}

			col++;
			far = 0;
			xobj = 0;
			yobj = 0;
			if (col >= width) {
				break;
			}
		}
	};

	/**
	 * renderObjs - Render the objects of the game scene using raycasting.
	*/
	void renderObjs() {
		angle = camA;
		for (int i = 0; i < objMapSize; i++) {
			sprite = objMap[i][0];
			x = objMap[i][1];
			y = objMap[i][2];

			sfar = sqrtf(powf(camX - x, 2) + powf(camY - y, 2));
			sdir = atan2f(y - camY, x - camX);

			if (sdir - angle > 3.14) {
				sdir -= 6.28;
			}

			if (sdir - angle < -3.14) {
				sdir += 6.28;
			}

			ssize = fminf(5000, height / sfar);
			shor = (sdir - angle + camB / 2) / steps - ssize / 2;

			if ((shor + ssize >= 0) && (shor < width)) {
				sfar *= cosf(sdir - angle);
				ssize /= cosf(sdir - angle);
				sver = (height - ssize) / 2;
				renderData[i + width][0] = 1;
				renderData[i + width][1] = sfar;
				renderData[i + width][2] = sprite;
				renderData[i + width][3] = shor;
				renderData[i + width][4] = sver;
				renderData[i + width][5] = ssize;
				renderData[i + width][6] = mapLight[int(x) + int(y) * mapWidth];
			}

			else {
				renderData[i + width][0] = -1;
			}
		}
	};

	/**
	 * show - Renders the game scene.
	 */
	void show() {

		renderWalls();
		renderObjs();

		/* Sort the rendering data in descending order based on the y position */
		for (int i = 0; i < renderDataSize; i++) {
			renderMax = i;
			for (int j = i; j < renderDataSize; j++) {
				if (renderData[j][1] > renderData[renderMax][1])
					renderMax = j;
			}

			/* Swap elements in the renderData array */
			renderDataMem = renderData[i];
			renderData[i] = renderData[renderMax];
			renderData[renderMax] = renderDataMem;
		}

		/* Rendering */
		/* Lock the texture to access its pixel data */
		if (!SDL_LockTexture(textures, NULL, (void **)&pixBuffer, &pitch)) {

			for (int y = 0; y < halfHeight; y++) {
				for (int x = 0; x < width; x++) {
					_fs = (camB / width) * (x - width / 2);
					_sax = camX + 1.f / y * (halfHeight * cosf(camA + _fs)) / cosf(_fs);
					_say = camY + 1.f / y * (halfHeight * sinf(camA + _fs)) / cosf(_fs);

					if (_say < mapHeight && _say > 0 && _sax < mapWidth && _sax > 0) {
						int ind = (int)_say * mapWidth + (int)_sax;
						mapFloor = flatFloor[ind];
						ceil_tile = flatCiel[ind];
						_sax = _sax - (int)_sax;
						_say = _say - (int)_say;
						int _cpx = (ceil_tile % mapWallWw) * mapWallW + _sax * mapWallW, _cpy = (ceil_tile / mapWallWw) * mapWallH + _say * mapWallH;
						int _fpx = (mapFloor % mapWallW) * mapWallW + _sax * mapWallW, _fpy = (mapFloor / mapWallWw) * mapWallH + _say * mapWallH;
						ceilColor = getpixel(wallSurf, _cpx, _cpy);
						
						/* ceiling */
						if (ceilColor != colorConv) {
							_fcr = RGBwallSurf[_cpx + _cpy * wallSurf->w][0];
							_fcg = RGBwallSurf[_cpx + _cpy * wallSurf->w][1];
							_fcb = RGBwallSurf[_cpx + _cpy * wallSurf->w][2];
							pixBuffer[halfHeight * width - y * width + x - width] = RGB(_fcr * mapLight[ind], _fcg * mapLight[ind], _fcb * mapLight[ind]);
						}

						/* ciel */
						else {
							slice = (camA + _fs) / 3.14;
							if (slice < 0) slice++;
							if (slice > 1) slice--;
							pixBuffer[halfHeight * width - y * width + x - width] = getpixel(cielSurf, slice * cielSurf->w, (float)cielSurf->h / (halfHeight) * (halfHeight - y));
						}

						/* floor */
						_fcr = RGBwallSurf[_fpx + _fpy * wallSurf->w][0];
						_fcg = RGBwallSurf[_fpx + _fpy * wallSurf->w][1];
						_fcb = RGBwallSurf[_fpx + _fpy * wallSurf->w][2];
						pixBuffer[y * width + x + halfHeight * width] = RGB(_fcr * mapLight[ind], _fcg * mapLight[ind], _fcb * mapLight[ind]);
					}
				}
			}

			for (int i = 0; i < renderDataSize; i++) {

				/* walls */
				if (renderData[i][0] == 0) {
					dop = 0;
					cheight = height / renderData[i][1] / cosf(renderData[i][3] - camA);

					if (cheight > height) {
						dop = (cheight - height) / 2;
						cheight = height;
					}

					/* wall image number from left border of the map */
					wallNumL = ((int)renderData[i][2] - 1) % mapWallWw; 
					/* wall image number from top border of the map */
					wallNumT = ((int)renderData[i][2] - 1) / mapWallWw; 

					int sp = (halfHeight - cheight / 2) - dop, ep = (halfHeight + cheight / 2) + dop - 1;
					int _cpx = wallNumL * mapWallW + (int)(mapWallW * renderData[i][5]), _cpy = 0;
					float _a1 = -halfHeight + cheight / 2 + dop, _a2 = ((float)mapWallH / (cheight + dop * 2));

					for (int j=halfHeight - cheight / 2; j < halfHeight + cheight / 2; j++) {
						_cpy = wallNumT * mapWallH + (j + _a1) * _a2;
						_fcr = RGBwallSurf[_cpx + _cpy * wallSurf->w][0];
						_fcg = RGBwallSurf[_cpx + _cpy * wallSurf->w][1];
						_fcb = RGBwallSurf[_cpx + _cpy * wallSurf->w][2];
						pixBuffer[(int)renderData[i][4] + j * width] = RGB(_fcr * renderData[i][6], _fcg * renderData[i][6], _fcb * renderData[i][6]);
					}
				}

				/* Objs */
				if (renderData[i][0] == 1) {
					wallNumL = (int)renderData[i][2] % mapObjsWw;
					wallNumT = renderData[i][2] / mapObjsWw;
					int _cpx = wallNumL * mapObjsW, _cpy = wallNumT * mapObjsH;
					int _sdy = (renderData[i][4] < 0 ? 0 : renderData[i][4]), _sdx = (renderData[i][3] < 0 ? 0 : renderData[i][3]),
						_edy = (renderData[i][4] + renderData[i][5] >= height ? height : renderData[i][4] + renderData[i][5]),
						_edx = (renderData[i][3] + renderData[i][5] >= width ? width : renderData[i][3] + renderData[i][5]);

					/* pixels out of the left bound */
					int xdt = _sdx - renderData[i][3], ydt = _sdy - renderData[i][4];
					int ind = 0;

					for (int y = _sdy; y < _edy; y++) {

						for (int x = _sdx; x < _edx; x++) {
							xx = _cpx + (x - _sdx + xdt) * mapObjsW / renderData[i][5];
							yy = _cpy + (y - _sdy + ydt) * mapObjsH / renderData[i][5];

							if (getpixel(objSurf, xx, yy) != colorConv) {
								ind = xx + yy * objSurf->w;
								_fcr = RGBobjSurf[ind][0];
								_fcg = RGBobjSurf[ind][1];
								_fcb = RGBobjSurf[ind][2];
								pixBuffer[x + y * width] = RGB(_fcr * renderData[i][6], _fcg * renderData[i][6], _fcb * renderData[i][6]);
							}
						}
					}
				}
			}

			/* Unlocked textures */
			SDL_UnlockTexture(textures);
			/* copied the rendered textures to display it on the screen.*/
			SDL_RenderCopy(renderer, textures, NULL, NULL);
		}

		else {
			std::cout << "Error\n";
		}
	};

	/**
	 * close - Frees the memory used by the wall and object textures.
	 */
	void close() {

		/* Free the wall texture */
		SDL_DestroyTexture(walls);
		/* Free the object texture */
		SDL_DestroyTexture(Objs);
	}

};

#endif /* _GAME_HPP_ */
