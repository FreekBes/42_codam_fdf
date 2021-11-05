/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:50:45 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 22:10:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "fdf.h"

void	draw_line(t_mlx_ctx *mlx, t_coords start, t_coords end, unsigned int c)
{
	t_coords	d;
	t_coords	s;
	int			err;
	int			e2;

	d.x = ft_abs(end.x - start.x);
	if (start.x < end.x)
		s.x = 1;
	else
		s.x = -1;
	d.y = ft_abs(end.y - start.y);
	if (start.y < end.y)
		s.y = 1;
	else
		s.y = -1;
	if (d.x > d.y)
		err = d.x / 2;
	else
		err = -d.y / 2;
	while (1)
	{
		put_pixel(mlx, start.x, start.y, c);
		if (start.x == end.x && start.y == end.y)
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

void	put_pixel(t_mlx_ctx *mlx, int h, int w, unsigned int c)
{
	char	*dst;

	h += mlx->offset.x;
	w += mlx->offset.y;
	if (h > mlx->res_h || w > mlx->res_w || h < 0 || w < 0)
		return ;
	dst = mlx->img.address + h * mlx->img.line_size
		+ w * (mlx->img.bits_per_pixel / 8);
	*(unsigned int *)dst = mlx_get_color_value(mlx->core, c);
}

static void	clear_img(t_mlx_ctx *mlx)
{
	ft_bzero(mlx->img.address, mlx->res_h * mlx->img.line_size);
}

int	draw_next_frame(t_fdf *fdf)
{
	handle_key_presses(fdf);
	clear_img(fdf->mlx);
	render_next_frame(fdf);
	mlx_put_image_to_window(fdf->mlx->core, fdf->mlx->win,
		fdf->mlx->img.img_ptr, 0, 0);
	return (1);
}
