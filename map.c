/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:43:17 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 23:20:19 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->colors = NULL;
	map->default_color = DEFAULT_COLOR;
	map->tile_size = RES_HEIGHT / DEFAULT_TILE_SIZE_FACTOR;
	map->translate_h = DEFAULT_TRANSLATE_H;
	map->width = 0;
	map->height = 0;
	return (map);
}

void	*free_map(t_map *map)
{
	ft_free_double_ptr((void **)map->map);
	ft_free_double_ptr((void **)map->colors);
	return (NULL);
}
