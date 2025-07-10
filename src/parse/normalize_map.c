#include "../../include/cub3d.h"

static char	*pad_line(char *src, int w)
{
	char	*dst;
	int		i;

	dst = (char *)malloc(w + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && i < w)
	{
		if (src[i] == ' ' || src[i] == '\n' || src[i] == '\r')
			dst[i] = '1';
		else
			dst[i] = src[i];
		++i;
	}
	while (i < w)
		dst[i++] = '1';
	dst[w] = '\0';
	return (dst);
}

int	normalize_map(t_map *map)
{
	int		y;
	char	*new_line;

	y = 0;
	while (y < map->h)
	{
		new_line = pad_line(map->grid[y], map->w);
		if (!new_line)
			return (-1);
		free(map->grid[y]);
		map->grid[y] = new_line;
		++y;
	}
	return (0);
}
