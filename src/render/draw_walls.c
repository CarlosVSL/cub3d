#include "../../include/cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	img->data[y * (img->line_len / 4) + x] = color;
}

static void	draw_slice(t_cub *c, int x, t_ray *r,
		int start, int end, double step, double tex_pos)
{
	int	y;
	int	tex_y;
	int	color;

	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos & (TEX_SIZE - 1);
		color = tex_sample(c, r->tex_id, r->tex_x, tex_y);
		if (r->side_hit == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&c->screen, x, y, color);
		tex_pos += step;
		++y;
	}
}

/* -------------------------------------------------------------------------- */
/*	Draw one textured vertical column                                         */
/* -------------------------------------------------------------------------- */
void	draw_walls(t_cub *c, int x, t_ray *r)
{
	int		line_h;
	int		start;
	int		end;
	double	step;
	double	tex_pos;

	line_h = (int)(WIN_H / r->dist);
	if (line_h < 1)
		line_h = 1;

	start = -line_h / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + WIN_H / 2;
	if (end >= WIN_H)
		end = WIN_H - 1;

	step = (double)TEX_SIZE / line_h;
	tex_pos = (start - WIN_H / 2 + line_h / 2) * step;

	draw_slice(c, x, r, start, end, step, tex_pos);
}