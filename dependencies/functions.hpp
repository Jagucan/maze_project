#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_


#include "game.hpp"


/* generate an error output if the condition is not met and end the program. */
#define ASSERT(cond, ...)			\
if (!cond)							\
{									\
	fprintf(stderr, __VA_ARGS__);	\
	exit(1);					    \
};

/* creates 32-bit color values from the individual color components. */
inline Uint32 RGB(uint32_t red, uint32_t green, uint32_t blue)
{
	return ((red << 16) | (green << 8) | blue);
};


/* get the value of a specific pixel in SDL surface. */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{

	/* stores the number of bytes per pixel of the surface. */
	int bites = surface->format->BytesPerPixel;

	/* represent the pixel at the (x, y) coordinates of the surface. */
	Uint8 *pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * bites;

	/* determine how the pixel value is interpreted and returned. */
	switch (bites)
	{
		/* if each pixel is represented by a single byte. */
		case 1:
			return (*pixel);

		/* if each pixel is represented by a two bytes (16 bits). */
		case 2:
			return (*(Uint16 *) pixel);

		/**
		 * if each pixel is represented by a three bytes (24 bits).
		 * Depending on the byte order, combine into a 32-bit color value.
		*/
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return (pixel[0] << 16 | pixel[1] << 8 | pixel[2]);
			else
				return (pixel[0] | pixel[1] << 8 | pixel[2] << 16);

		/* if each pixel is represented by a four bytes (32 bits). */
		case 4:
			return (*(Uint32 *) pixel);

		/* If the value of bits does not match the previous cases, it returns 0. */
		default:
			return (0);
	}

};

#endif /* _FUNCTIONS_HPP_ */
