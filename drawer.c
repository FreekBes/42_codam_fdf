/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:50:45 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/10 17:40:51 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
