/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:35 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:35 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#include "../../include/cub3d.h"

/* Inicializa el estado base y recuerda el directorio del mapa */
static int init_basics(t_cub *cub, const char *map_path)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->map_dir = ft_dirname(map_path);
	if (!cub->map_dir)
		return (-1);
	return (0);
}

int	cub3d_run(const char *map_path)
{
	t_cub	cub;

	/* 1) Estado básico + map_dir */
	if (init_basics(&cub, map_path))
	{
		cub_error(&cub, "Out of memory while resolving map directory");
		return (-1);
	}

	/* 2) Parser (.cub): ids, colores y mapa (incluye check_map) */
	if (parse_scene(&cub, map_path))
	{
		cub_error(&cub, "Invalid scene file: bad identifiers or map format");
		return (-1);
	}

	/* 3) MiniLibX */
	if (init_mlx(&cub))
	{
		cub_error(&cub, "Failed to initialize graphics (MiniLibX/display)");
		return (-1);
	}

	/* 4) Texturas (ruta inexistente o tamaño != 64x64) */
	if (init_textures(&cub))
	{
		cub_error(&cub, "Texture load failed: missing file or wrong size (64x64 required)");
		return (-1);
	}

	/* 5) Jugador (debe existir exactamente un spawn) */
	if (init_player(&cub))
	{
		cub_error(&cub, "Invalid map: missing or multiple player spawn");
		return (-1);
	}

	/* 6) Hooks de ventana */
	if (set_hooks(&cub))
	{
		cub_error(&cub, "Failed to install window hooks");
		return (-1);
	}

	/* 7) Loop principal */
	mlx_loop(cub.mlx);

	/* 8) Limpieza normal al salir del loop */
	cub_cleanup(&cub);
	return (0);
}