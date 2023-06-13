#ifndef _MAPS_H_
#define _MAPS_H_


/* maps dimensions */
#define MAPWIDTH 11
#define MAPHEIGHT 11

/* ---------------------------------------------------------------- */

/* add walls or columns on the map */
int map[MAPWIDTH * MAPHEIGHT] = {
	4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4,
};

/* add textures to change the floor design. */
int map_floor[MAPWIDTH * MAPHEIGHT] = {
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
	3, 6, 0, 0, 0, 0, 0, 0, 0, 6, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
	3, 6, 0, 0, 0, 0, 0, 0, 0, 6, 3,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
};

/* add textures to simulate the roof */
int map_ciel[MAPWIDTH * MAPHEIGHT] = {
	0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
	0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
	0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
	0, 5, 5, 8, 8, 8, 8, 8, 5, 5, 0,
	0, 5, 5, 8, 8, 8, 8, 8, 5, 5, 0,
	0, 5, 5, 8, 8, 8, 8, 8, 5, 5, 0,
	0, 5, 5, 8, 8, 8, 8, 8, 5, 5, 0,
	0, 5, 5, 8, 8, 8, 8, 8, 5, 5, 0,
	0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
	0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
	0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
};

/* lights or shadows on the map */
float map_light[MAPWIDTH * MAPHEIGHT] = {
	.1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1,
	.1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1,
	.1, .1, .2, .2, .3, .4, .3, .2, .2, .1, .1,
	.1, .1, .3,  1,  1,  1,  1,  1, .3, .1, .1,
	.1, .1, .4,  1,  1,  1,  1,  1, .4, .1, .1,
	.1, .1, .4,  1,  1,  1,  1,  1, .4, .1, .1,
	.1, .1, .4,  1,  1,  1,  1,  1, .4, .1, .1,
	.1, .1, .3,  1,  1,  1,  1,  1, .3, .1, .1,
	.1, .1, .2, .2, .3, .4, .3, .2, .2, .1, .1,
	.1, .1, .1, .1, .1, .1, .1, .1, .1, .1, .1,
};

/* objects on the map */
float map_objs[3][3] = {
	{3, 1.5, 1.5},
	{3, 8.5, 1.5},
	{0, 2.5, 2.5}
};

/* ---------------------------------------------------------------- */
#endif /* _MAPS_H_*/
