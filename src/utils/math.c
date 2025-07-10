#include "../../include/cub3d.h"

double	ft_abs_d(double v)
{
	if (v < 0.0)
		return (-v);
	return (v);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
