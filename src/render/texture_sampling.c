#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*	Return ARGB color from a 64×64 texture.									*/
/* -------------------------------------------------------------------------- */
int	tex_sample(t_cub *cub, int id, int x, int y)
{
	if (id < 0 || id >= 4)
		return (0);
	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
		return (0);
	return (cub->textures[id].img.data[y * TEX_SIZE + x]);
}
