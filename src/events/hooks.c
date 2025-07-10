#include "../../include/cub3d.h"

int	set_hooks(t_cub *cub)
{
	if (!cub || !cub->win)
		return (-1);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, exit_program, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	return (0);
}
