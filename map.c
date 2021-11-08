/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:43:17 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 17:30:23 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "fdf.h"

/**
 * Allocate and initialize a map structure
 * @return		A map structure
 */
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
	if (map->tile_size <= 0)
		return (ft_free(map));
	map->relief_factor = DEFAULT_RELIEF_FACTOR;
	map->width = 0;
	map->height = 0;
	return (map);
}

/**
 * Free a map structure
 * @param map	A map structure to free
 * @return		Always returns NULL
 */
void	*free_map(t_map *map)
{
	ft_free_double_ptr((void **)map->map);
	ft_free_double_ptr((void **)map->colors);
	ft_free(map);
	return (NULL);
}
