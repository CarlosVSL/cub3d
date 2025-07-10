#include "../../include/cub3d.h"

/* guarda la ruta eliminando \n, \r y espacios finales --------------------- */
static int	store_texture(t_cub *cub, int idx, char *path)
{
	char	*clean;
	size_t	len;

	if (cub->textures[idx].path)
		return (-1);
	clean = skip_spaces(path);
	len = ft_strlen(clean);
	while (len && (clean[len - 1] == '\n'
			|| clean[len - 1] == '\r' || clean[len - 1] == ' '))
		--len;
	cub->textures[idx].path = ft_substr(clean, 0, len);
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

