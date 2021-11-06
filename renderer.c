/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 20:25:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 20:17:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

static void	draw_line_to_point(t_fdf *fdf, t_coords *s, int e_x, int e_y)
{
	t_gradient	g;

	g.start = DEFAULT_COLOR;
	g.end = DEFAULT_COLOR;
	if (fdf->map->colors[s->y][s->x] != 0)
		g.start = fdf->map->colors[s->y][s->x];
	if (fdf->map->colors[e_y][e_x] != 0)
		g.end = fdf->map->colors[e_y][e_x];
	if (g.start != DEFAULT_COLOR || g.end != DEFAULT_COLOR)
		draw_line_g(fdf->mlx, fdf->map->iso_map[s->y][s->x], &fdf->map->iso_map[e_y][e_x], &g);
	else
		draw_line(fdf->mlx, fdf->map->iso_map[s->y][s->x], &fdf->map->iso_map[e_y][e_x], DEFAULT_COLOR);
}

static void	draw_lines(t_fdf *fdf)
{
	t_coords	s;

	s.y = 0;
	while (s.y < fdf->map->height)
	{
		s.x = 0;
		while (s.x < fdf->map->width)
		{
			if (s.x > 0)
				draw_line_to_point(fdf, &s, s.x - 1, s.y);
			if (s.y > 0)
				draw_line_to_point(fdf, &s, s.x, s.y - 1);
			s.x++;
		}
		s.y++;
	}
}

int	render_next_frame(t_fdf *fdf)
{
	int				changed;
	int				h;
	int				w;
	t_coords		coords;
	static double	rot;
	static double	last_tile_size;
	static t_coords	last_offset;

	changed = 0;
	if (rot == 0)
	{
		ft_putendl_fd("Calculating isographic coordinates...", 1);
		rot = 0.75;
		h = 0;
		while (h < fdf->map->height)
		{
			w = 0;
			while (w < fdf->map->width)
			{
				coords.x = h * fdf->map->tile_size + (w * fdf->map->tile_size * rot);
				coords.y = w * fdf->map->tile_size - (h * fdf->map->tile_size);
				coords.x -= (fdf->map->map[h][w] * fdf->map->translate_h * fdf->map->tile_size);
				(fdf->map->iso_map[h][w]).x = coords.x;
				(fdf->map->iso_map[h][w]).y = coords.y;
				w++;
			}
			h++;
		}
	}
	if (last_tile_size == 0 || fdf->map->tile_size != last_tile_size ||
		last_offset.x != fdf->mlx->offset.x || last_offset.y != fdf->mlx->offset.y)
	{
		last_tile_size = fdf->map->tile_size;
		last_offset.x = fdf->mlx->offset.x;
		last_offset.y = fdf->mlx->offset.y;
		ft_putendl_fd("Clearing image...", 1);
		clear_img(fdf->mlx);
		ft_putendl_fd("Drawing pixels for coordinates...", 1);
		h = 0;
		while (h < fdf->map->height)
		{
			w = 0;
			while (w < fdf->map->width)
			{
				if (fdf->map->colors[h][w] != 0)
					put_pixel(fdf->mlx, coords.x, coords.y, fdf->map->colors[h][w]);
				else
					put_pixel(fdf->mlx, coords.x, coords.y, DEFAULT_COLOR);
				w++;
			}
			h++;
		}
		ft_putendl_fd("Drawing lines...", 1);
		draw_lines(fdf);
		changed = 1;
	}
	return (changed);
}
