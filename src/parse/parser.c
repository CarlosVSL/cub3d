#include "../../include/cub3d.h"

int	is_map_line(const char *s);

/* store a duplicate into the list ------------------------------------------ */
static int	store_line(t_list **lst, char *line)
{
	char	*dup;

	dup = ft_strdup(line);
	if (!dup)
		return (-1);
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
			return (free(line), -1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

/* extract identifiers & colours, stop at first map line -------------------- */
static int	process_meta(t_cub *c, t_list *n)
{
	char	*str;

	while (n)
	{
		str = (char *)n->content;
		if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
			if (parse_texture_line(c, str))
				return (-1);
		if (*str == 'F')
			if (parse_color_line(&c->floor_color, str))
				return (-1);
		if (*str == 'C')
			if (parse_color_line(&c->ceil_color, str))
				return (-1);
		if (is_map_line(str))
			break ;
		n = n->next;
	}
	if (!n)
		return (-1);
	return (init_map(c, str));
}

/* PUBLIC ------------------------------------------------------------------- */
int	parse_scene(t_cub *cub, const char *path)
{
	int		fd;
	t_list	*lst;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lst = NULL;
	if (read_file(fd, &lst) || process_meta(cub, lst))
		return (ft_lstclear(&lst, free), close(fd), -1);
	ft_lstclear(&lst, free);
	close(fd);
	return (0);
}
