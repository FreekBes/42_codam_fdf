/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_checks.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 17:58:34 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/10 18:03:28 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Check whether it is necessary to recalculate the position of all map points
 * @param fdf	A pointer to the main fdf structure
 */
int	check_if_recalc_needed(t_fdf *fdf)
{
	static double	last_rotation;
	static double	last_tsize;
	static double	last_rel_factor;

	if (fdf->mlx->rotation != last_rotation || fdf->map->tile_size != last_tsize
		|| fdf->map->relief_factor != last_rel_factor)
	{
		last_rotation = fdf->mlx->rotation;
		last_tsize = fdf->map->tile_size;
		last_rel_factor = fdf->map->relief_factor;
		return (1);
	}
	return (0);
}

/**
 * Check whether it is necessary to redraw the frame
 * @param fdf	A pointer to the main fdf structure
 */
int	check_if_redraw_needed(t_fdf *fdf)
{
	static t_coords	last_offset;

	if (last_offset.x != fdf->mlx->offset.x
		|| last_offset.y != fdf->mlx->offset.y)
	{
		last_offset.x = fdf->mlx->offset.x;
		last_offset.y = fdf->mlx->offset.y;
		return (1);
	}
	return (0);
}
