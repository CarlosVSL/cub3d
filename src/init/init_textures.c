#include "../../include/cub3d.h"

static void *try_load(void *mlx, const char *path, int *w, int *h)
{
	if (file_exists(path))
		return (mlx_xpm_file_to_image(mlx, (char *)path, w, h));
	return (NULL);
}

static int	load_tex(t_cub *c, t_texture *tex, char *orig)
{
	void	*img;
	char	*path_mapdir;     /* map_dir + orig            */
	char	*path_parent;     /* parent(map_dir) + orig    */

	img = NULL;
	path_mapdir = NULL;
	path_parent = NULL;

	/* 1) Tal cual está escrito en el .cub --------------------------------- */
	img = try_load(c->mlx, orig, &tex->img.w, &tex->img.h);

	/* 2) map_dir + ruta (si es relativa) ---------------------------------- */
	if (!img && orig[0] != '/')
	{
		path_mapdir = path_join(c->map_dir, orig);
		if (path_mapdir)
			img = try_load(c->mlx, path_mapdir,
					&tex->img.w, &tex->img.h);
	}

	/* 3) parent(map_dir) + ruta ------------------------------------------- */
	if (!img && orig[0] != '/')
	{
		char	*parent = ft_path_parent(c->map_dir);
		if (parent)
		{
			path_parent = path_join(parent, orig);
			free(parent);
			if (path_parent)
				img = try_load(c->mlx, path_parent,
						&tex->img.w, &tex->img.h);
		}
	}

	/* --- liberar memoria temporal --------------------------------------- */
	if (path_mapdir)
		free(path_mapdir);
	if (path_parent)
		free(path_parent);

	/* --- validar y almacenar -------------------------------------------- */
	if (!img || tex->img.w != TEX_SIZE || tex->img.h != TEX_SIZE)
	{
		if (img)
			mlx_destroy_image(c->mlx, img);
		return (-1);
	}
	tex->img.ptr = img;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (tex->img.data)
		return (0);
	return (-1);

/* ------------------------------------------------------------------------ */
int	init_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_tex(cub, &cub->textures[i], cub->textures[i].path))
			return (-1);
		++i;
	}
	return (0);
}
