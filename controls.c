/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 21:52:32 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/10 16:48:33 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Handle offset (arrow keys)
 * @param fdf	The main fdf struct
 */
static void	handle_offset_keys(t_fdf *fdf)
{
	int		up_down;
	int		left_right;

	up_down = 0;
	left_right = 0;
	if (fdf->key_stat.up)
		up_down += 1 + fdf->map->tile_size * 0.2 + fdf->map->width * 0.05;
	if (fdf->key_stat.down)
		up_down -= 1 + fdf->map->tile_size * 0.2 + fdf->map->width * 0.05;
	if (fdf->key_stat.left)
		left_right += 1 + fdf->map->tile_size * 0.2 + fdf->map->width * 0.05;
	if (fdf->key_stat.right)
		left_right -= 1 + fdf->map->tile_size * 0.2 + fdf->map->width * 0.05;
	fdf->mlx->offset.y += left_right;
	fdf->mlx->offset.x += up_down;
}

/**
 * Handle zoom and relief (min, plus, square bracket keys)
 * @param fdf	The main fdf struct
 */
static void	handle_zoom_and_relief(t_fdf *fdf)
{
	double	zoom;
	double	relief;

	zoom = 1;
	relief = 0;
	if (fdf->key_stat.min)
		zoom -= 0.05;
	if (fdf->key_stat.plus)
		zoom += 0.05;
	if (fdf->key_stat.sq_br_l)
		relief -= 0.01;
	if (fdf->key_stat.sq_br_r)
		relief += 0.01;
	fdf->map->tile_size *= zoom;
	if (fdf->map->tile_size < 1)
		fdf->map->tile_size = 1;
	else if (fdf->map->tile_size > RES_WIDTH)
		fdf->map->tile_size = RES_WIDTH;
	fdf->map->relief_factor += relief;
}

/**
 * Handle rotation (comma and dot keys)
 * @param fdf	The main fdf struct
 */
static void	handle_rotation(t_fdf *fdf)
{
	double	rot;

	rot = 0;
	if (fdf->key_stat.comma)
		rot += 0.01;
	if (fdf->key_stat.dot)
		rot -= 0.01;
	fdf->mlx->rotation += rot;
	if (fdf->mlx->rotation < 0)
		fdf->mlx->rotation = 0;
	else if (fdf->mlx->rotation > fdf->mlx->max_rotation)
		fdf->mlx->rotation = fdf->mlx->max_rotation;
}

/**
 * Change fdf parameters based on which keys are currently pressed
 * @param fdf	The main fdf struct
 */
void	handle_key_presses(t_fdf *fdf)
{
	handle_offset_keys(fdf);
	handle_zoom_and_relief(fdf);
	handle_rotation(fdf);
}
