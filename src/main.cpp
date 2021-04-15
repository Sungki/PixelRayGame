#define PUNITY_IMPLEMENTATION
#include "PixelRay.h"

int x = 0;
int y = 0;

int init()
{
	return 1;
}

void step()
{
	pixel_draw(x++, y, 3);
	if (x >= 300)
	{
		x = 0;
		y++;
	}
}