/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:22 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:22 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* -------------------------------------------------------------------------- */
/*  Trim leading spaces/tabs                                                  */
/* -------------------------------------------------------------------------- */
char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		++s;
	return (s);
}

/* -------------------------------------------------------------------------- */
/*  Read an integer, advance ptr, store in out                                */
/* -------------------------------------------------------------------------- */
int	parse_int(const char **str, int *out)
{
	int	val;

	val = 0;
	*str = skip_spaces((char *)*str);
	if (**str < '0' || **str > '9')
		return (-1);
	while (**str >= '0' && **str <= '9')
	{
		val = val * 10 + (**str - '0');
		++(*str);
	}
	*out = val;
	return (0);
}

/* -------------------------------------------------------------------------- */
/*  Una línea es de mapa si:                                                  */
/*   - No es un identificador (NO, SO, WE, EA, F, C)                          */
/*   - Contiene SOLO {' ', '0','1','N','S','E','W'} hasta fin de línea        */
/*   - Contiene al menos un tile real (no solo espacios)                      */
/*  Nota: se permiten tabs iniciales como en headers; en mapa, espacio es sig.*/
/* -------------------------------------------------------------------------- */
static int	is_identifier(const char *s)
{
	if ((s[0] == 'N' && s[1] == 'O') || (s[0] == 'S' && s[1] == 'O'))
		return (1);
	if ((s[0] == 'W' && s[1] == 'E') || (s[0] == 'E' && s[1] == 'A'))
		return (1);
	if (*s == 'F' || *s == 'C')
		return (1);
	return (0);
}

int	is_map_line(const char *s)
{
	int	has_tile;

	while (*s == '\t')
		++s;
	if (*s == '\0')
		return (0);
	if (is_identifier(s))
		return (0);
	has_tile = 0;
	while (*s && *s != '\n' && *s != '\r')
	{
		if (*s == ' ' || *s == '0' || *s == '1'
			|| *s == 'N' || *s == 'S' || *s == 'E' || *s == 'W')
		{
			if (*s != ' ')
				has_tile = 1;
		}
		else
			return (0);
		++s;
	}
	return (has_tile);
}
