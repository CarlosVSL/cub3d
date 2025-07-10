#include "../../include/cub3d.h"

/* combine three bytes into 0xRRGGBB -------------------------------------- */
static int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/* PUBLIC: lee línea 'F 220,100,0' o 'C 30,60,90' ------------------------- */
int	parse_color_line(int *dst, char *l)
{
	const char	*s;
	int			r;
	int			g;
	int			b;

	s = skip_spaces(l + 1);
	if (parse_int(&s, &r) || *s++ != ',' || parse_int(&s, &g) \
		|| *s++ != ',' || parse_int(&s, &b))
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	*dst = rgb_to_int(r, g, b);
	return (0);
}
