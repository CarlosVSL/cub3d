#include "../../include/cub3d.h"

#ifndef EPS
# define EPS 1e-9
#endif
#ifndef MAX_MOVE_STEP
# define MAX_MOVE_STEP  0.25   /* longitud máxima por subpaso */
#endif

void    apply_wall_sliding(t_cub *c, double dx, double dy);

/* -------------------------------------------------------------------------- */
static void subdivide_movement_steps(t_cub *c, double total_dx, double total_dy,
                                     int steps)
{
    const double step_dx = total_dx / (double)steps;
    const double step_dy = total_dy / (double)steps;
    int i = 0;

    while (i < steps)
    {
        apply_wall_sliding(c, step_dx, step_dy);
        ++i;
    }
}

/* -------------------------------------------------------------------------- */
/*  PUBLIC: subdivisión adaptativa del movimiento                             */
/* -------------------------------------------------------------------------- */
void    subdiv_move(t_cub *c, double total_dx, double total_dy)
{
    double dist;
    int    steps;

    if (fabs(total_dx) < EPS && fabs(total_dy) < EPS)
        return ;
    /* Atajo: si nada en la trayectoria bloquea, aplica entero */
    if (!is_wall(c, c->player.pos.x + total_dx, c->player.pos.y + total_dy))
    {
        c->player.pos.x += total_dx;
        c->player.pos.y += total_dy;
        return ;
    }
    dist  = sqrt(total_dx * total_dx + total_dy * total_dy);
    if (dist <= MAX_MOVE_STEP)
    {
        apply_wall_sliding(c, total_dx, total_dy);
        return ;
    }
    steps = (int)ceil(dist / MAX_MOVE_STEP);
    if (steps < 1) steps = 1;
    subdivide_movement_steps(c, total_dx, total_dy, steps);
}
