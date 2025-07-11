#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Devuelve el directorio de `path` (sin el nombre del fichero)              */
/*  Ej.: "/foo/bar/map.cub"  ->  "/foo/bar"                                   */
/* -------------------------------------------------------------------------- */
char	*ft_dirname(const char *path)
{
	const char	*slash;

	if (!path)
		return (NULL);
	slash = strrchr(path, '/');
	if (!slash)                               /* sin '/' -> directorio "."   */
		return (ft_strdup("."));
	return (ft_substr(path, 0, slash - path)); /* dup sin el '/' final        */
}

/* -------------------------------------------------------------------------- */
/*  Une `dir` + "/" + `file`  →  string nuevo                                 */
/* -------------------------------------------------------------------------- */
char	*path_join(const char *dir, const char *file)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, file);
	free(tmp);
	return (joined);
}

char	*ft_path_parent(const char *dir)
{
	return (path_join(dir, ".."));
}

/* 0 = no existe, 1 = existe y es legible */
int	file_exists(const char *path)
{
	return (access(path, F_OK) == 0);
}