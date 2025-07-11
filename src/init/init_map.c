#include "../../include/cub3d.h"

/* dynamic grid growth ------------------------------------------------------ */
static int	grow_grid(char ***grid, int *cap)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * ((*cap * 2) + 1));
	if (!tmp)
		return (-1);
	i = 0;
	while (i < *cap)
	{
		tmp[i] = (*grid)[i];
		++i;
	}
	free(*grid);
	*grid = tmp;
	*cap *= 2;
	return (0);
}

/* duplicate & store one line, stripping trailing newlines ------------------ */
static int	push_line(char *src, char ***g, int *h, int *cap, int *w)
{
	char	*dup;
	char	*end;
	int		len;

	if (*h >= *cap && grow_grid(g, cap))
		return (-1);
	dup = ft_strdup(src);
	if (!dup)
		return (-1);
	end = dup + ft_strlen(dup) - 1;
	while (end >= dup && (*end == '\n' || *end == '\r'))
		*end-- = '\0';
	(*g)[*h] = dup;
	len = ft_strlen(dup);
	if (len > *w)
		*w = len;
	++(*h);
	return (0);
}


/* skip until first map line ------------------------------------------------ */
static int	skip_to_map(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line && !is_map_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}

/* read map block ----------------------------------------------------------- */
static int	read_map(int fd, t_cub *cub, int *cap)
{
	char	*line;

	if (skip_to_map(fd, &line))
		return (-1);
	while (line && is_map_line(line))
	{
		if (push_line(line, &cub->map.grid, &cub->map.h, cap, &cub->map.w))
			return (free(line), -1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

/* PUBLIC ------------------------------------------------------------------- */
int	init_map(t_cub *cub, const char *path)
{
	int	fd;
	int	cap;

	cap = 16;
	cub->map.grid = (char **)malloc(sizeof(char *) * (cap + 1));
	if (!cub->map.grid)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read_map(fd, cub, &cap))
		return (close(fd), -1);
	cub->map.grid[cub->map.h] = NULL;
	close(fd);
	return (normalize_map(&cub->map));
}
