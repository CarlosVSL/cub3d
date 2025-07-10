#include "../../include/cub3d.h"

static int	init_game(t_cub *cub, const char *map_path)
{
	ft_bzero(cub, sizeof(t_cub));
	if (parse_scene(cub, map_path))
		return (-1);
	if (init_mlx(cub))
		return (-1);
	if (init_textures(cub))
		return (-1);
	if (init_player(cub))
		return (-1);
	return (0);
}

int	cub3d_run(const char *map_path)
{
	t_cub	cub;

	if (init_game(&cub, map_path))
	{
		cub_cleanup(&cub);
		return (-1);
	}
	if (set_hooks(&cub))
	{
		cub_cleanup(&cub);
		return (-1);
	}
	mlx_loop(cub.mlx);
	cub_cleanup(&cub);
	return (0);
}
