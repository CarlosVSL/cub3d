#ifndef MLX_CUSTOM_H
# define MLX_CUSTOM_H

# include "structs.h"

t_img	img_create(void *mlx, int w, int h);
void	img_destroy(void *mlx, t_img *img);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
