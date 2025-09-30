/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:54 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:54 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/* drena GNL hasta EOF para liberar la stash del fd ------------------------ */
static void	gnl_drain(int fd)
{
	char	*s;

	while ((s = get_next_line(fd)) != NULL)
		free(s);
}

/* true si la línea es solo espacios/tabs/CR/LF --------------------------- */
static int	is_blank_line(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
		++s;
	return (*s == '\0');
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

/* lee la sección de mapa y valida que no haya contenido tras el mapa ------ */
int	read_map(int fd, t_cub *cub, int *cap)
{
	char	*line;
	int		err;

	err = 0;
	if (skip_to_map(fd, &line))
		return (-1);
	while (line && is_map_line(line))
	{
		if (push_line(line, &cub->map.grid, &cub->map.h, cap, &cub->map.w))
			return (free(line), gnl_drain(fd), -1);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		/* Si hay algo no-vacío después del mapa => error (el mapa debe ser lo último) */
		if (!is_blank_line(line))
			err = -1;
		free(line);
		gnl_drain(fd); /* asegura Valgrind limpio: libera stash de GNL */
	}
	return (err);
}
