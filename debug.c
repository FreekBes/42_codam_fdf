/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 19:34:21 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 18:44:24 by fbes          ########   odam.nl         */
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
