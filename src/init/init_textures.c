#include "../../include/cub3d.h"

/* ------------------------------------------------------------------------ */
static int	load_tex(t_cub *c, t_texture *t, char *path)
{
	char	*full;
	int		need_free;

	if (path[0] != '/')
	{
		full = path_join(c->map_dir, path);
		if (!full)
			return (-1);
		need_free = 1;
	}
	else
	{
		full = path;
		need_free = 0;
	}

	t->img.ptr = mlx_xpm_file_to_image(c->mlx, full, &t->img.w, &t->img.h);

	if (need_free)
		free(full);

	if (!t->img.ptr)
		return (-1);
	if (t->img.w != TEX_SIZE || t->img.h != TEX_SIZE)
	{
		mlx_destroy_image(c->mlx, t->img.ptr);
		return (-1);
	}
	t->img.data = (int *)mlx_get_data_addr(t->img.ptr, &t->img.bpp,
			&t->img.line_len, &t->img.endian);
	if (!t->img.data)
	{
		mlx_destroy_image(c->mlx, t->img.ptr);
		return (-1);
	}
	return (0);
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
