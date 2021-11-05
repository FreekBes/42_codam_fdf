/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:50:45 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 18:51:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	draw_next_frame(t_fdf *fdf)
{
	//render_next_frame(fdf);
	mlx_put_image_to_window(fdf->mlx->core, fdf->mlx->win,
		fdf->mlx->img.img_ptr, 0, 0);
	mlx_do_sync(fdf->mlx->core);
	return (1);
}
