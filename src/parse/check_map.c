#include "../../include/cub3d.h"

/* ------------------------------------------------------------------------ */
static int	validate_cell(t_map *m, int y, int x, int *sp)
{
	if (!is_walk(m->grid[y][x]))
		return (0);
	if (out_of_bounds(m, y - 1, x) || out_of_bounds(m, y + 1, x)
		|| out_of_bounds(m, y, x - 1) || out_of_bounds(m, y, x + 1))
		return (-1);
	if (m->grid[y][x] == 'N' || m->grid[y][x] == 'S'
		|| m->grid[y][x] == 'E' || m->grid[y][x] == 'W')
		++(*sp);
	return (0);
}

/* ------------------------------------------------------------------------ */
int	check_map(t_cub *cub)
{
	t_map	*m;
	int		y;
	int		x;
	int		spawn;

	m = &cub->map;
	spawn = 0;
	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (validate_cell(m, y, x, &spawn))
				return (-1);
			++x;
		}
		++y;
	}
	if (spawn != 1)
		return (-1);
	return (0);
}
