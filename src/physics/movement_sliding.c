#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Búsqueda binaria de la fracción máxima del desplazamiento sin colisión    */
/* -------------------------------------------------------------------------- */
static double binary_search_safe_distance(t_cub *c,
                                          double x0, double y0,
                                          double dx, double dy)
{
    double low = 0.0, high = 1.0, safe = 0.0;

    while (high - low > EPS)
    {
        double mid = 0.5 * (low + high);
        if (!is_wall(c, x0 + dx * mid, y0 + dy * mid))
        {
            safe = mid;
            low  = mid;
        }
        else
            high = mid;
    }
    return safe;
}

/* -------------------------------------------------------------------------- */
/*  Punto de extensión si quisieras refinar (mantengo estructura del bonus)   */
/* -------------------------------------------------------------------------- */
double  find_safe_distance(t_cub *c, double x0, double y0, double dx, double dy)
{
    (void)c; (void)x0; (void)y0; (void)dx; (void)dy;
    /* Se podría iterar refinando normal de pared, etc.; el binario basta. */
    return binary_search_safe_distance(c, x0, y0, dx, dy);
}

static void handle_remaining_movement(t_cub *c, double dx, double dy, double t)
{
    const double rx = dx * (1.0 - t);
    const double ry = dy * (1.0 - t);

    if (fabs(rx) > EPS || fabs(ry) > EPS)
        try_smooth_move(c, rx, ry);
}

/* -------------------------------------------------------------------------- */
/*  PUBLIC: aplica deslizamiento suave en caso de colisión parcial            */
/* -------------------------------------------------------------------------- */
void    apply_wall_sliding(t_cub *c, double dx, double dy)
{
    const double t = find_safe_distance(c, c->player.pos.x, c->player.pos.y, dx, dy);

    if (t > EPS)
    {
        c->player.pos.x += dx * t;
        c->player.pos.y += dy * t;
        handle_remaining_movement(c, dx, dy, t);
    }
    else
        try_smooth_move(c, dx, dy);
}
