#include "../../include/cub3d.h"

/* store path only once ---------------------------------------------------- */
static int	store_texture(t_cub *cub, int idx, char *path)
{
	if (cub->textures[idx].path)
		return (-1);
	cub->textures[idx].path = ft_strdup(skip_spaces(path));
	return (!cub->textures[idx].path);
}

/* ---------- PUBLIC: texture identifiers (NO / SO / WE / EA) ------------- */
int	parse_texture_line(t_cub *cub, char *l)
{
	char	*s;

	s = skip_spaces(l);
	if (!ft_strncmp(s, "NO ", 3))
		return (store_texture(cub, DIR_NORTH, s + 3));
	if (!ft_strncmp(s, "SO ", 3))
		return (store_texture(cub, DIR_SOUTH, s + 3));
	if (!ft_strncmp(s, "WE ", 3))
		return (store_texture(cub, DIR_WEST, s + 3));
	if (!ft_strncmp(s, "EA ", 3))
		return (store_texture(cub, DIR_EAST, s + 3));
	return (-1);
}

