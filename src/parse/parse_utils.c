#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*	Trim leading spaces/tabs                                                  */
/* -------------------------------------------------------------------------- */
char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		++s;
	return (s);
}

/* -------------------------------------------------------------------------- */
/*	Read an integer, advance ptr, store in out                                */
/* -------------------------------------------------------------------------- */
int	parse_int(const char **str, int *out)
{
	int	val;

	val = 0;
	*str = skip_spaces((char *)*str);
	if (**str < '0' || **str > '9')
		return (-1);
	while (**str >= '0' && **str <= '9')
	{
		val = val * 10 + (**str - '0');
		++(*str);
	}
	*out = val;
	return (0);
}

/* -------------------------------------------------------------------------- */
/*	Detect whether a line belongs to the map                                  */
/* -------------------------------------------------------------------------- */
int	is_map_line(const char *s)
{
	while (*s == ' ')
		++s;
	return (*s == '1' || *s == '0' || *s == 'N' \
		|| *s == 'S' || *s == 'E' || *s == 'W');
}