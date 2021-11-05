/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 20:25:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 22:17:56 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>

static void	draw_lines(t_fdf *fdf)
{
	int			h;
	int			w;

	h = 0;
	while (h < fdf->map->height)
	{
		w = 0;
		while (w < fdf->map->width)
		{
			if (w > 0)
				draw_line(fdf->mlx, fdf->map->iso_map[h][w], fdf->map->iso_map[h][w - 1], 0x00FFFFFF);
			if (w < fdf->map->width - 1)
				draw_line(fdf->mlx, fdf->map->iso_map[h][w], fdf->map->iso_map[h][w + 1], 0x00FFFFFF);
			if (h > 0)
				draw_line(fdf->mlx, fdf->map->iso_map[h][w], fdf->map->iso_map[h - 1][w], 0x00FFFFFF);
			if (h < fdf->map->height - 1)
				draw_line(fdf->mlx, fdf->map->iso_map[h][w], fdf->map->iso_map[h + 1][w], 0x00FFFFFF);
			w++;
		}
		h++;
	}
}

void	render_next_frame(t_fdf *fdf)
{
	int			h;
	int			w;
	t_coords	coords;

	h = 0;
	while (h < fdf->map->height)
	{
		w = 0;
		while (w < fdf->map->width)
		{
			coords.x = h * fdf->map->tile_size + (w * fdf->map->tile_size * 0.75);
			coords.y = w * fdf->map->tile_size - (h * fdf->map->tile_size);
			coords.x -= (fdf->map->map[h][w] * 0.05 * fdf->map->tile_size);
			(fdf->map->iso_map[h][w]).x = coords.x;
			(fdf->map->iso_map[h][w]).y = coords.y;
			put_pixel(fdf->mlx, coords.x, coords.y, 0x00FFFFFF);
			w++;
		}
		h++;
	}
	draw_lines(fdf);
}
