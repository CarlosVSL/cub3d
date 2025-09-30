/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:47 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Rotación del jugador (igual que base, expuesta para reutilizar)           */
/* -------------------------------------------------------------------------- */
void    rotate_player(t_player *p, double angle)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = p->dir.x;
    old_plane_x = p->plane.x;
    p->dir.x = old_dir_x * cos(angle) - p->dir.y * sin(angle);
    p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);
    p->plane.x = old_plane_x * cos(angle) - p->plane.y * sin(angle);
    p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

/* -------------------------------------------------------------------------- */
/*  Acumula desplazamiento WASD (frente/lateral con base en dir y plane)      */
/* -------------------------------------------------------------------------- */
static void calculate_movement_wasd(t_cub *c, double *dx, double *dy)
{
    if (c->keys.w)
    {
        *dx += c->player.dir.x * MOVE_SPEED;
        *dy += c->player.dir.y * MOVE_SPEED;
    }
    if (c->keys.s)
    {
        *dx -= c->player.dir.x * MOVE_SPEED;
        *dy -= c->player.dir.y * MOVE_SPEED;
    }
    if (c->keys.a)
    {
        *dx += c->player.dir.y * MOVE_SPEED;
        *dy -= c->player.dir.x * MOVE_SPEED;
    }
    if (c->keys.d)
    {
        *dx -= c->player.dir.y * MOVE_SPEED;
        *dy += c->player.dir.x * MOVE_SPEED;
    }
}

/* -------------------------------------------------------------------------- */
/*  Rotación con flechas                                                      */
/* -------------------------------------------------------------------------- */
static void handle_rotation(t_cub *c)
{
    if (c->keys.left)
        rotate_player(&c->player, -ROT_SPEED);
    if (c->keys.right)
        rotate_player(&c->player, ROT_SPEED);
}

/* -------------------------------------------------------------------------- */
/*  PUBLIC: Actualización de movimiento (mejorada con subdivisión + sliding)  */
/* -------------------------------------------------------------------------- */
int     movement_update(t_cub *c)
{
    double  total_dx = 0.0;
    double  total_dy = 0.0;

    calculate_movement_wasd(c, &total_dx, &total_dy);
    if (fabs(total_dx) > MIN_MOVE_DISTANCE || fabs(total_dy) > MIN_MOVE_DISTANCE)
        subdiv_move(c, total_dx, total_dy);
    handle_rotation(c);
    return (0);
}
