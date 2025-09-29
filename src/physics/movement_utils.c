#include "../../include/cub3d.h"

#ifndef EPS
# define EPS 1e-9
#endif

static void try_move_x(t_cub *c, double dx)
{
    double nx;

    if (fabs(dx) < EPS)
        return ;
    nx = c->player.pos.x + dx;
    if (!is_wall(c, nx, c->player.pos.y))
        c->player.pos.x = nx;
}

static void try_move_y(t_cub *c, double dy)
{
    double ny;

    if (fabs(dy) < EPS)
        return ;
    ny = c->player.pos.y + dy;
    if (!is_wall(c, c->player.pos.x, ny))
        c->player.pos.y = ny;
}

/* -------------------------------------------------------------------------- */
/*  Movimiento suave eje a eje (para restos tras colisión)                    */
/* -------------------------------------------------------------------------- */
void    try_smooth_move(t_cub *c, double dx, double dy)
{
    try_move_x(c, dx);
    try_move_y(c, dy);
}
