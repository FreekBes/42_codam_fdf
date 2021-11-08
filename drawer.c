/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:50:45 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 17:35:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"

/**
 * Check if a coordinate is off-screen
 * @param t_coords	The coordinates to check
 * @return			Returns 1 if off-screen, 0 if not
 */
int	is_off_screen(t_mlx_ctx *mlx, t_coords coords)
{
	coords.x += mlx->offset.x;
	coords.y += mlx->offset.y;
	if (coords.x < 0 || coords.x >= mlx->res_h)
		return (1);
	else if (coords.y < 0 || coords.y >= mlx->res_w)
		return (1);
	return (0);
}

/**
 * Initialize the drawing of a line for Bresenham's Line Algorithm
 * A simple explanation on how this algorithm works can be found here:
 * www.ques10.com/p/22015/explain-bresenhams-line-drawing-algorithm-in-detai/
 * Also available on web.archive.org in case link goes down
 * @param d		Delta coordinates
 * @param s		S coordinates
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
	int			e2;

	err = init_line_draw(&d, &s, &start, end);
	while (1)
	{
		put_pixel(mlx, start.x, start.y, c);
		if (start.x == end->x && start.y == end->y)
			break ;
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			start.x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			start.y += s.y;
		}
	}
}

/**
 * Draw a line using Bresenham's Line Algorithm in a color gradient
 * @param mlx	A pointer to a MLX context struct
 * @param start	The coordinates of the line's starting position
 * @param end	The coordinates of the line's end position
 * @param g		The color gradient to draw the line in
 */
void	draw_line_g(t_mlx_ctx *mlx, t_coords start, t_coords *end, t_gradient *g)
{
	t_coords	d;
	t_coords	s;
	int			err;
	int			e2;
	int			i;
	int			len;

	err = init_line_draw(&d, &s, &start, end);
	len = (int)round(sqrt(pow(end->x - start.x, 2) + pow(end->y - start.y, 2)));
	i = 0;
	while (1)
	{
		put_pixel(mlx, start.x, start.y, get_gradient_color(g->start, g->end, (double)i / (double)len));
		if (start.x == end->x && start.y == end->y)
			break ;
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			start.x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			start.y += s.y;
		}
		i++;
	}
}

/**
 * Get the address of a pixel on the canvas
 * @param mlx	A pointer to a MLX context struct
 * @param h		At which horizontal line to get the pixel
 * @param w		At which vertical line to get the pixel
 * @return		A pointer to said pixel
 */
static char	*get_pixel_addr(t_mlx_ctx *mlx, int h, int w)
{
	char	*dst;

	h += mlx->offset.x;
	w += mlx->offset.y;
	if (h >= mlx->res_h || w >= mlx->res_w || h < 0 || w < 0)
		return (NULL);
	dst = mlx->img.address + h * mlx->img.line_size
		+ w * (mlx->img.bits_per_pixel / 8);
	return (dst);
}

/**
 * Draw a pixel to the mlx image instance's canvas
 * @param mlx	A pointer to a MLX context struct
 * @param h		At which horizontal line to draw the pixel (y)
 * @param w		At which vertical line to draw the pixel (x)
 * @param c		The color of the pixel to draw
 */
void	put_pixel(t_mlx_ctx *mlx, int h, int w, unsigned int c)
{
	char	*dst;

	dst = get_pixel_addr(mlx, h, w);
	if (!dst)
		return ;
	*(unsigned int *)dst = mlx_get_color_value(mlx->core, c);
}

/**
 * Draw a pixel to the mlx image instance's canvas, but only if the pixel
 * is empty right now
 * @param mlx	A pointer to a MLX context struct
 * @param h		At which horizontal line to draw the pixel (y)
 * @param w		At which vertical line to draw the pixel (x)
 * @param c		The color of the pixel to draw
 */
void	put_pixel_e(t_mlx_ctx *mlx, int h, int w, unsigned int c)
{
	char	*dst;

	dst = get_pixel_addr(mlx, h, w);
	if (!dst)
		return ;
	if (*(unsigned int *)dst == 0)
		*(unsigned int *)dst = mlx_get_color_value(mlx->core, c);
}

/**
 * Clear the mlx image instance's canvas
 * @param mlx	A pointer to a MLX context struct
 */
void	clear_img(t_mlx_ctx *mlx)
{
	ft_bzero(mlx->img.address, mlx->res_h * mlx->img.line_size);
}

/**
 * Draw a frame
 * @param fdf	A pointer to the main fdf struct
 * @return		Always returns 1
 */
int	draw_next_frame(t_fdf *fdf)
{
	handle_key_presses(fdf);
	mlx_sync(MLX_SYNC_WIN_FLUSH_CMD, fdf->mlx->win);
	render_next_frame(fdf, 0);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, fdf->mlx->img.img_ptr);
	mlx_put_image_to_window(fdf->mlx->core, fdf->mlx->win,
		fdf->mlx->img.img_ptr, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, fdf->mlx->win);
	return (1);
}
