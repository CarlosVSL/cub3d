#include "../../include/cub3d.h"

/* walkable cell ------------------------------------------------------------ */
int	is_walk(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* safe index inside map ---------------------------------------------------- */
int	out_of_bounds(t_map *m, int y, int x)
{
	return (y < 0 || x < 0 || y >= m->h || x >= m->w);
}