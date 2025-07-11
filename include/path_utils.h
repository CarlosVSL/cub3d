#ifndef PATH_UTILS_H
# define PATH_UTILS_H

/* duplica la parte “directorio” de una ruta (sin el nombre del fichero)     */
char	*ft_dirname(const char *path);

/* une dir + "/" + file  →  nuevo malloc                                      */
char	*path_join(const char *dir, const char *file);

#endif
