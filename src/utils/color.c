#include "../../include/cub3d.h"

int	argb(int a, int r, int g, int b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int	rgb_to_int(int r, int g, int b)
{
	return (argb(0xFF, r, g, b));
}
