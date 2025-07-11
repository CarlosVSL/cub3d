#include "../../include/cub3d.h"

/* ------------------------------------------------------------------------ */
static double	non_zero(double v)
{
	if (fabs(v) < EPS)
	{
		if (v < 0)
			return (-EPS);
		return (EPS);
	}
	return (v);
}

/* ------------------------------------------------------------------------ */
static void	set_step_side(t_cub *c, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side.x = (c->player.pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->map_x + 1.0 - c->player.pos.x) * r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step_y = -1;
		r->side.y = (c->player.pos.y - r->map_y) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->side.y = (r->map_y + 1.0 - c->player.pos.y) * r->delta.y;
	}
}

/* ------------------------------------------------------------------------ */
static void	set_ray_dist(t_cub *c, t_ray *r)
{
	if (r->side_hit == 0)
		r->dist = (r->map_x - c->player.pos.x + (1 - r->step_x) * 0.5) / r->dir.x;
	else
		r->dist = (r->map_y - c->player.pos.y + (1 - r->step_y) * 0.5) / r->dir.y;
	r->dist = fabs(r->dist);
	if (r->dist < EPS)
		r->dist = EPS;
}

/* ------------------------------------------------------------------------ */
static void	ray_init(t_cub *c, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_W - 1.0;
	r->dir.x = non_zero(c->player.dir.x + c->player.plane.x * camera_x);
	r->dir.y = non_zero(c->player.dir.y + c->player.plane.y * camera_x);
	r->map_x = (int)c->player.pos.x;
	r->map_y = (int)c->player.pos.y;
	r->delta.x = fabs(1.0 / r->dir.x);
	r->delta.y = fabs(1.0 / r->dir.y);
	set_step_side(c, r);
}

/* ------------------------------------------------------------------------ */
static void	dda(t_cub *c, t_ray *r)
{
	int	hit = 0;

	while (!hit)
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->map_x += r->step_x;
			r->side_hit = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->map_y += r->step_y;
			r->side_hit = 1;
		}
		if (c->map.grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
	set_ray_dist(c, r);
}

/* ------------------------------------------------------------------------ */
static void	set_tex_info(t_cub *c, t_ray *r)
{
	double	wall_x;

	if (r->side_hit == 0)
		wall_x = c->player.pos.y + r->dist * r->dir.y;
	else
		wall_x = c->player.pos.x + r->dist * r->dir.x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * (double)TEX_SIZE);
	if (r->side_hit == 0 && r->dir.x > 0)
		r->tex_id = DIR_WEST;
	else if (r->side_hit == 0)
		r->tex_id = DIR_EAST;
	else if (r->dir.y > 0)
		r->tex_id = DIR_NORTH;
	else
		r->tex_id = DIR_SOUTH;
}

/* ------------------------------------------------------------------------ */
void	raycaster(t_cub *cub)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		ray_init(cub, &r, x);
		dda(cub, &r);
		set_tex_info(cub, &r);
		draw_walls(cub, x, &r);
		++x;
	}
}
