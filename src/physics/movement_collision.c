#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Parámetros por defecto                                                     */
/* -------------------------------------------------------------------------- */
#ifndef COLLISION_RADIUS
# define COLLISION_RADIUS  0.20   /* radio físico del jugador (en celdas) */
#endif
#ifndef EPS
# define EPS 1e-9
#endif

/* -------------------------------------------------------------------------- */
/*  Stub de colisión con sprites/otros (ajústalo si tu base tiene sprites)    */
/*  Devuelve 0 para ignorar sprites; no requiere headers extra.               */
/* -------------------------------------------------------------------------- */
static int check_sprite_collision(t_cub *c, double x, double y)
{
    (void)c; (void)x; (void)y;
    return (0);
}

/* -------------------------------------------------------------------------- */
/*  Test de punto sólido en el grid                                           */
/* -------------------------------------------------------------------------- */
static int is_point_wall(t_cub *c, double x, double y)
{
    char tile;

    if (y < 0 || y >= c->map.h || x < 0 || x >= c->map.w)
        return (1);
    tile = c->map.grid[(int)y][(int)x];
    if (tile == '1')
        return (1);
    /* Si en el futuro añades puertas 'D' u otros sólidos, añádelos aquí */
    return (check_sprite_collision(c, x, y));
}

/* -------------------------------------------------------------------------- */
static int check_collision_edges(t_cub *c, double x, double y, double r)
{
    if (is_point_wall(c, x,     y - r) ||
        is_point_wall(c, x,     y + r) ||
        is_point_wall(c, x - r, y    ) ||
        is_point_wall(c, x + r, y    ))
        return (1);
    return (0);
}

static int check_collision_corners(t_cub *c, double x, double y, double r)
{
    if (is_point_wall(c, x - r, y - r) ||
        is_point_wall(c, x + r, y - r) ||
        is_point_wall(c, x - r, y + r) ||
        is_point_wall(c, x + r, y + r))
        return (1);
    return (0);
}

/* -------------------------------------------------------------------------- */
/*  PUBLIC: colisión con radio                                                */
/* -------------------------------------------------------------------------- */
int  is_wall(t_cub *c, double x, double y)
{
    const double r = COLLISION_RADIUS;

    if (x - r < 0 || x + r >= c->map.w || y - r < 0 || y + r >= c->map.h)
        return (1);
    if (is_point_wall(c, x, y))
        return (1);
    if (check_collision_edges(c, x, y, r))
        return (1);
    if (check_collision_corners(c, x, y, r))
        return (1);
    return (0);
}

/* -------------------------------------------------------------------------- */
/*  Movimiento con deslizamiento simple (fallback de seguridad)               */
/* -------------------------------------------------------------------------- */
void  wall_slide_move(t_cub *c, double dx, double dy)
{
    double nx = c->player.pos.x + dx;
    double ny = c->player.pos.y + dy;

    if (!is_wall(c, nx, ny))
    {
        c->player.pos.x = nx;
        c->player.pos.y = ny;
        return ;
    }
    if (!is_wall(c, nx, c->player.pos.y))
        c->player.pos.x = nx;
    else if (!is_wall(c, c->player.pos.x, ny))
        c->player.pos.y = ny;
}
