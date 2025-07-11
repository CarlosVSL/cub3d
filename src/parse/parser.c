#include "../../include/cub3d.h"

/* store a duplicate into the list, stripping trailing newlines ------------ */
static int	store_line(t_list **lst, char *line)
{
	char	*dup;
	char	*end;

	dup = ft_strdup(line);
	if (!dup)
		return (-1);
	end = dup + ft_strlen(dup) - 1;
	while (end >= dup && (*end == '\n' || *end == '\r'))
		*end-- = '\0';
	ft_lstadd_back(lst, ft_lstnew(dup));
	return (0);
}

/* read whole file ---------------------------------------------------------- */
static int	read_file(int fd, t_list **lst)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (store_line(lst, line))
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

/* process metadata and then initialize the map ---------------------------- */
static int	process_meta(t_cub *cub, t_list *node, const char *path)
{
	char	*str;
	char	*s;

	while (node)
	{
		str = (char *)node->content;
		s = skip_spaces(str);

		if ((*s == 'N' || *s == 'S' || *s == 'W' || *s == 'E')
			&& parse_texture_line(cub, s))
			return (-1);
		if (*s == 'F' && parse_color_line(&cub->floor_color, s))
			return (-1);
		if (*s == 'C' && parse_color_line(&cub->ceil_color, s))
			return (-1);
		if (is_map_line(s))
			break ;
		node = node->next;
	}
	if (!node)
		return (-1);
	return (init_map(cub, path));
}

/* PUBLIC: parse entire scene file (.cub) ---------------------------------- */
int	parse_scene(t_cub *cub, const char *path)
{
	int		fd;
	t_list	*lst;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lst = NULL;
	if (read_file(fd, &lst) || process_meta(cub, lst, path)
		|| check_map(cub))
	{
		ft_lstclear(&lst, free);
		close(fd);
		return (-1);
	}
	ft_lstclear(&lst, free);
	close(fd);
	return (0);
}
