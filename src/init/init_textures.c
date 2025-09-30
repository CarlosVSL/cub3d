/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:02 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:02 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* --- utils locales -------------------------------------------------------- */
static int is_nonempty_path(const char *s)
{
	return (s && s[0] != '\0');
}

static void *try_load(void *mlx, const char *path, int *w, int *h)
{
	if (!is_nonempty_path(path))
		return (NULL);
	if (!file_exists(path))
		return (NULL);
	return mlx_xpm_file_to_image(mlx, (char *)path, w, h);
}

/* --- carga una textura ---------------------------------------------------- */
static int	load_tex(t_cub *c, t_texture *tex, char *orig)
{
	void	*img = NULL;
	char	*path_mapdir = NULL;   /* map_dir + orig          */
	char	*path_parent = NULL;   /* parent(map_dir) + orig  */

	/* validar entradas */
	if (!c || !tex || !is_nonempty_path(orig))
		return (-1);

	/* 1) Tal cual está escrito en el .cub */
	img = try_load(c->mlx, orig, &tex->img.w, &tex->img.h);

	/* 2) map_dir + ruta (si es relativa) */
	if (!img && orig[0] != '/')
	{
		path_mapdir = path_join(c->map_dir, orig);
		if (path_mapdir)
			img = try_load(c->mlx, path_mapdir, &tex->img.w, &tex->img.h);
	}

	/* 3) parent(map_dir) + ruta */
	if (!img && orig[0] != '/')
	{
		char *parent = ft_path_parent(c->map_dir);
		if (parent)
		{
			path_parent = path_join(parent, orig);
			free(parent);
			if (path_parent)
				img = try_load(c->mlx, path_parent, &tex->img.w, &tex->img.h);
		}
	}

	/* liberar temporales (free acepta NULL) */
	free(path_mapdir);
	free(path_parent);

	/* validar imagen y dimensiones */
	if (!img || tex->img.w != TEX_SIZE || tex->img.h != TEX_SIZE)
	{
		if (img)
			mlx_destroy_image(c->mlx, img);
		return (-1);
	}

	/* almacenar */
	tex->img.ptr = img;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	return (tex->img.data ? 0 : -1);
}

/* --- público -------------------------------------------------------------- */
int	init_textures(t_cub *cub)
{
	int i;

	if (!cub)
		return (-1);
	for (i = 0; i < 4; ++i)
	{
		/* si el parser dejó path NULL o "", fallará aquí sin segfault */
		if (load_tex(cub, &cub->textures[i], cub->textures[i].path))
			return (-1);
	}
	return (0);
}