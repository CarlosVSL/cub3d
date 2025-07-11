#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <mlx.h>
# include "libft.h"

# include "defines.h"
# include "enums.h"
# include "structs.h"
# include "loop.h"
# include "mlx_custom.h"
# include "path_utils.h"

/* -------------------------------------------------------------------------- */
/*  High-level                                                               */
/* -------------------------------------------------------------------------- */
int     cub3d_run(const char *map_path);
void    cub_cleanup(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Init                                                                     */
/* -------------------------------------------------------------------------- */
int     init_mlx(t_cub *cub);
int     init_textures(t_cub *cub);
int     init_player(t_cub *cub);
int     init_map(t_cub *cub, const char *path);

/* -------------------------------------------------------------------------- */
/*  Timing                                                                   */
/* -------------------------------------------------------------------------- */
double  timer_delta(void);
void    timer_sleep(long target_fps, double dt);

/* -------------------------------------------------------------------------- */
/*  Parsing                                                                  */
/* -------------------------------------------------------------------------- */
int     parse_scene(t_cub *cub, const char *path);
int     parse_color_line(int *dst, char *l);
int     parse_texture_line(t_cub *cub, char *l);
int     normalize_map(t_map *map);
int     check_map(t_cub *cub);
int     is_map_line(const char *s);

/* -------------------------------------------------------------------------- */
/*  Utils (parse)                                                            */
/* -------------------------------------------------------------------------- */
char    *skip_spaces(char *s);
int     parse_int(const char **str, int *out);

/* -------------------------------------------------------------------------- */
/*  Utils (map)                                                              */
/* -------------------------------------------------------------------------- */
int     is_walk(char c);
int     out_of_bounds(t_map *m, int y, int x);

/* -------------------------------------------------------------------------- */
/*  Game logic                                                                */
/* -------------------------------------------------------------------------- */
int     movement_update(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Rendering                                                                 */
/* -------------------------------------------------------------------------- */
void    draw_floor_ceil(t_cub *cub);
void    raycaster(t_cub *cub);
int     tex_sample(t_cub *cub, int id, int x, int y);
void	draw_walls(t_cub *c, int x, t_ray *r);

/* -------------------------------------------------------------------------- */
/*  Utils (error / free)                                                      */
/* -------------------------------------------------------------------------- */
int     cub_error(t_cub *cub, const char *msg);
void    free_arr(char **arr);

/* -------------------------------------------------------------------------- */
/*  Vector operations                                                         */
/* -------------------------------------------------------------------------- */
t_vec   vec_add(t_vec a, t_vec b);
t_vec   vec_mul(t_vec v, double s);
double  vec_len(t_vec v);
t_vec   vec_norm(t_vec v);

/* -------------------------------------------------------------------------- */
/*  Math helpers                                                              */
/* -------------------------------------------------------------------------- */
double  ft_abs_d(double v);
double  ft_max_d(double a, double b);
double  ft_min_d(double a, double b);

#endif
