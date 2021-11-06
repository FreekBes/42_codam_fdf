/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 19:34:21 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:08:45 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

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

void	reset_viewport(t_fdf *fdf)
{
	fdf->map->tile_size = RES_HEIGHT / fdf->map->height * 0.5;
	fdf->map->relief_factor = DEFAULT_relief_factor;
	fdf->map->default_color = DEFAULT_COLOR;
	fdf->mlx->offset.x = RES_HEIGHT * 0.1;
	fdf->mlx->offset.y = RES_WIDTH * 0.4;
}
