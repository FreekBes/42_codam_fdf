/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 17:09:50 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/10 18:02:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "fdf.h"

/**
 * Initialize the drawing of a line for Bresenham's Line Algorithm
 * A simple explanation on how this algorithm works can be found here:
 * www.ques10.com/p/22015/explain-bresenhams-line-drawing-algorithm-in-detai/
 * Also available on web.archive.org in case link goes down
 * Basically how it works is that we have an x and a y position for every
 * drawing position. For every draw, we check if we're closer (in a line on a
 * real graph) to x + 1 or just x + 0, if closer to x + 1 we increment x.
 * This allows for the drawing of a smooth-ish line on a computer screen.
 * @param d		Delta coordinates
 * @param s		S coordinates (defines the direction of the line: up or down)
 * @param st	Starting coordinates
 * @param en	Ending coordinates
 * @return		The error margin
 */
static int	init_line_draw(t_coords *d, t_coords *s, t_coords *st, t_coords *en)
{
	d->x = ft_abs(en->x - st->x);
	if (st->x < en->x)
		s->x = 1;
	else
		s->x = -1;
	d->y = ft_abs(en->y - st->y);
	if (st->y < en->y)
		s->y = 1;
	else
		s->y = -1;
	if (d->x > d->y)
		return (d->x / 2);
	else
		return (-d->y / 2);
}

/**
 * Increase x and y
 * (see comment above for explanation)
 * @param err	The error margin
 * @param cur	The coordinates of the current drawpoint (= start)
 * @param d		Delta coordinates
 * @param s		S coordinates (defines the direction of the line: up or down)
 */
static void	increase_x_and_y(int *err, t_coords *cur, t_coords *d, t_coords *s)
{
	int			e2;

	e2 = *err;
	if (e2 > -d->x)
	{
		*err -= d->y;
		cur->x += s->x;
	}
	if (e2 < d->y)
	{
		*err += d->x;
		cur->y += s->y;
	}
}

/**
 * Draw a line using Bresenham's Line Algorithm in a static color
 * @param mlx	A pointer to a MLX context struct
 * @param start	The coordinates of the line's starting position
 * @param end	The coordinates of the line's end position
 * @param c		The color to draw the line in
 */
void	draw_line(t_mlx_ctx *mlx, t_coords start, t_coords *end, unsigned int c)
{
	t_coords	d;
	t_coords	s;
	int			err;

	err = init_line_draw(&d, &s, &start, end);
	while (1)
	{
		put_pixel(mlx, start.x, start.y, c);
		if (start.x == end->x && start.y == end->y)
			break ;
		increase_x_and_y(&err, &start, &d, &s);
	}
}

/**
 * Draw a line using Bresenham's Line Algorithm in a color gradient
 * @param mlx	A pointer to a MLX context struct
 * @param strt	The coordinates of the line's starting position
 * @param end	The coordinates of the line's end position
 * @param g		The color gradient to draw the line in
 */
void	draw_line_g(t_mlx_ctx *mlx, t_coords strt, t_coords *end, t_gradient *g)
{
	t_coords	d;
	t_coords	s;
	int			err;
	int			i;
	int			len;

	err = init_line_draw(&d, &s, &strt, end);
	len = (int)round(sqrt(pow(end->x - strt.x, 2) + pow(end->y - strt.y, 2)));
	i = 0;
	while (1)
	{
		put_pixel(mlx, strt.x, strt.y,
			get_gradient_color(g->start, g->end, (double)i / (double)len));
		if (strt.x == end->x && strt.y == end->y)
			break ;
		increase_x_and_y(&err, &strt, &d, &s);
		i++;
	}
}
