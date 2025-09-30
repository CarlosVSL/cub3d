/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:59 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:59 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_plane(t_player *p)
{
	if (p->dir.x == -1)
		p->plane = (t_vec){0, FOV};
	else if (p->dir.x == 1)
		p->plane = (t_vec){0, -FOV};
	else if (p->dir.y == -1)
		p->plane = (t_vec){FOV, 0};
	else
		p->plane = (t_vec){-FOV, 0};
}

int	init_player(t_cub *cub)
{
	int		y = -1;
	int		x;
	char	c;

	while (++y < cub->map.h)
	{
		x = -1;
		while (++x < cub->map.w)
		{
			c = cub->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cub->player.pos = (t_vec){x + 0.5, y + 0.5};
				cub->map.grid[y][x] = '0';
				cub->player.dir = (t_vec){(c == 'E') - (c == 'W'),
					(c == 'S') - (c == 'N')};
				set_plane(&cub->player);
				return (0);
			}
		}
	}
	return (-1);
}
