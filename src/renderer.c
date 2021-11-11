/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 20:25:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:41:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "fdf_settings.h"
#include "fdf_drawer.h"

/**
 * Draw a line from map point to another map point
 * The method will automatically start drawing gradients if necessary
 * @param fdf	A pointer to the main fdf structure
 * @param s		The line's starting coordinates
 * @param e_x	The line's ending x coordinate
 * @param e_y	The line's ending y coordinate
 */
static void	draw_line_to_point(t_fdf *fdf, t_coords *s, int e_x, int e_y)
{
	t_gradient	g;

	if (is_off_screen(fdf->mlx, fdf->map->iso_map[s->y][s->x]) &&
			is_off_screen(fdf->mlx, fdf->map->iso_map[e_y][e_x]))
		return ;
	g.start = DEFAULT_COLOR;
	g.end = DEFAULT_COLOR;
	if (fdf->map->colors[s->y][s->x] != 0)
		g.start = fdf->map->colors[s->y][s->x];
	if (fdf->map->colors[e_y][e_x] != 0)
		g.end = fdf->map->colors[e_y][e_x];
	if (g.start != DEFAULT_COLOR || g.end != DEFAULT_COLOR)
		draw_line_g(fdf->mlx, fdf->map->iso_map[s->y][s->x],
			&fdf->map->iso_map[e_y][e_x], &g);
	else
		draw_line(fdf->mlx, fdf->map->iso_map[s->y][s->x],
			&fdf->map->iso_map[e_y][e_x], DEFAULT_COLOR);
}

/**
 * Draw lines from all points to their neighbors
 * @param fdf	A pointer to the main fdf structure
 */
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

/**
 * Calculate the positions of the coordinates of the map
 * @param fdf	A pointer to the main fdf structure
 */
static void	calculate_iso_coordinates(t_fdf *fdf)
{
	int			h;
	int			w;
	t_zcoords	coords;

	ft_putendl_fd("Calculating isographic coordinates...", 1);
	h = 0;
	while (h < fdf->map->height)
	{
		w = 0;
		while (w < fdf->map->width)
		{
			coords.z = fdf->map->alts[h][w] \
					* fdf->map->relief_factor * fdf->map->tile_size;
			coords.x = -coords.z + (w * fdf->map->tile_size \
					+ h * fdf->map->tile_size) * sin(fdf->mlx->rotation);
			coords.y = (w * fdf->map->tile_size - h * fdf->map->tile_size) \
					* cos(fdf->mlx->rotation);
			(fdf->map->iso_map[h][w]).x = coords.x;
			(fdf->map->iso_map[h][w]).y = coords.y;
			w++;
		}
		h++;
	}
}

/**
 * Render all the points of the map
 * @param fdf	A pointer to the main fdf structure
 */
static void	render_points(t_fdf *fdf)
{
	int			h;
	int			w;

	ft_putendl_fd("Drawing pixels for coordinates...", 1);
	h = 0;
	while (h < fdf->map->height)
	{
		w = 0;
		while (w < fdf->map->width)
		{
			if (fdf->map->colors[h][w] != 0)
				put_pixel(fdf->mlx, (fdf->map->iso_map[h][w]).x,
					(fdf->map->iso_map[h][w]).y, fdf->map->colors[h][w]);
			else
				put_pixel(fdf->mlx, (fdf->map->iso_map[h][w]).x,
					(fdf->map->iso_map[h][w]).y, DEFAULT_COLOR);
			w++;
		}
		h++;
	}
}

/**
 * Render a frame into the mlx canvas
 * @param fdf		A pointer to the main fdf structure
 * @param forced	Set to 1 to forcefully redraw the whole frame without
 * 					optimalizations
 * @return			Returns 1 if part of the frame has been redrawn, else 0
 */
int	render_next_frame(t_fdf *fdf, int forced)
{
	int				changed;

	changed = 0;
	if (forced || check_if_recalc_needed(fdf))
	{
		calculate_iso_coordinates(fdf);
		changed = 1;
	}
	if (forced || changed || check_if_redraw_needed(fdf))
	{
		ft_putendl_fd("Clearing image...", 1);
		clear_img(fdf->mlx);
		render_points(fdf);
		if (ALWAYS_DRAW_LINES || no_keys_pressed(&fdf->key_stat))
		{
			ft_putendl_fd("Drawing lines...", 1);
			draw_lines(fdf);
		}
		changed = 1;
	}
	return (changed);
}
