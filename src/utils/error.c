#include "../../include/cub3d.h"

int	cub_error(t_cub *cub, const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		while (*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
	}
	cub_cleanup(cub);
	return (-1);
}
