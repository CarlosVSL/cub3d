#include "../../include/cub3d.h"

int	exit_program(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub_cleanup(cub);
	exit(0);
	return (0);
}
