#include "../../include/cub3d.h"

static void *try_load(void *mlx, const char *path, int *w, int *h)
{
	if (file_exists(path))
		return (mlx_xpm_file_to_image(mlx, (char *)path, w, h));
	return (NULL);
}

static int	load_tex(t_cub *c, t_texture *tex, char *orig)
{
	char	*paths[3] = {NULL, NULL, NULL};
	void	*img = NULL;

	/* 1) tal cual se encuentra en el .cub */
	paths[0] = orig;

	/* 2) map_dir + ruta (solo si no empieza por '/') */
	if (orig[0] != '/')
		paths[1] = path_join(c->map_dir, orig);

	/* 3) parent(map_dir) + ruta  (caso map + textures en carpetas hermanas) */
	if (orig[0] != '/')
	{
		char *parent = ft_path_parent(c->map_dir);
		if (parent)
		{
			paths[2] = path_join(parent, orig);
			free(parent);
		}
	}

	for (int i = 0; i < 3 && !img && paths[i]; ++i)
		img = try_load(c->mlx, paths[i], &tex->img.w, &tex->img.h);

	if (paths[1]) free(paths[1]);
	if (paths[2]) free(paths[2]);

	if (!img || tex->img.w != TEX_SIZE || tex->img.h != TEX_SIZE)
	{
		if (img) mlx_destroy_image(c->mlx, img);
		return (-1);
	}
	tex->img.ptr = img;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
				&tex->img.line_len, &tex->img.endian);
	return (tex->img.data ? 0 : -1);
}


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
