/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 19:34:21 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 19:12:07 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

/**
 * Print a map configuration for debugging purposes
 * @param map	The map to print
 */
void	print_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			ft_putnbr_fd(map->map[i][j], 1);
			ft_putstr_fd(" (", 1);
			ft_putnbr_base_fd(map->colors[i][j], "0123456789ABCDEF", 1);
			ft_putstr_fd(") ", 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/**
 * Reset the viewport of the window (map is rendered in center again)
 * @param fdf	The main fdf structure
 */
void	reset_viewport(t_fdf *fdf)
{
	fdf->map->tile_size = RES_HEIGHT / fdf->map->height * 0.5;
	fdf->map->relief_factor = DEFAULT_RELIEF_FACTOR;
	fdf->map->default_color = DEFAULT_COLOR;
	fdf->mlx->offset.x = RES_HEIGHT * 0.1;
	fdf->mlx->offset.y = RES_WIDTH * 0.4;
	fdf->mlx->rotation = degree_to_radians(30);
}
