#include "../../include/cub3d.h"

static int	is_wall(t_cub *c, double x, double y)
{
	if (y < 0 || y >= c->map.h || x < 0 || x >= c->map.w)
		return (1);
	return (c->map.grid[(int)y][(int)x] == '1');
}

static void	move(t_cub *c, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = c->player.pos.x + dx;
	ny = c->player.pos.y + dy;
	if (!is_wall(c, nx, c->player.pos.y))
		c->player.pos.x = nx;
	if (!is_wall(c, c->player.pos.x, ny))
		c->player.pos.y = ny;
}

static void	rotate(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	p->dir.x = old_dir_x * cos(angle) - p->dir.y * sin(angle);
	p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
	p->plane.x = old_plane_x * cos(angle) - p->plane.y * sin(angle);
	p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

int	movement_update(t_cub *c)
{
	if (c->keys.w)
		move(c, c->player.dir.x * MOVE_SPEED, c->player.dir.y * MOVE_SPEED);
	if (c->keys.s)
		move(c, -c->player.dir.x * MOVE_SPEED, -c->player.dir.y * MOVE_SPEED);
	if (c->keys.a)
		move(c, -c->player.dir.y * MOVE_SPEED, c->player.dir.x * MOVE_SPEED);
	if (c->keys.d)
		move(c, c->player.dir.y * MOVE_SPEED, -c->player.dir.x * MOVE_SPEED);
	if (c->keys.left)
		rotate(&c->player, -ROT_SPEED);
	if (c->keys.right)
		rotate(&c->player, ROT_SPEED);
	return (0);
}
