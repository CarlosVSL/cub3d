/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_subdiv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:40 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:40 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


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
