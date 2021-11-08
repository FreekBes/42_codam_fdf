/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 20:24:02 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 19:25:37 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "fdf.h"
#include "mlx.h"

/**
 * Create an mlx image instance in an mlx context struct
 * @param ctx	A pointer to an mlx context struct
 */
static void	create_img(t_mlx_ctx *ctx)
{
	ctx->img.img_ptr = mlx_new_image(ctx->core, ctx->res_w, ctx->res_h);
	ctx->img.address = mlx_get_data_addr(ctx->img.img_ptr,
			&ctx->img.bits_per_pixel, &ctx->img.line_size, &ctx->img.endian);
}

/**
 * Reduce the window size if it's too big
 * @param ctx	A pointer to an mlx context struct
 * @todo
 */
static void	catch_max_res_exception(t_mlx_ctx *ctx)
{
	int		scr_w;
	int		scr_h;

	mlx_get_screen_size(ctx->core, &scr_w, &scr_h);
	if (ctx->res_w > (unsigned int)scr_w)
		ctx->res_w = (unsigned int)scr_w;
	if (ctx->res_h > (unsigned int)scr_h)
		ctx->res_h = (unsigned int)scr_h;
}

/**
 * Free an mlx context structure
 * @param ctc	An mlx context structure
 * @return		Always returns NULL
 */
void	*free_mlx_context(t_mlx_ctx *ctx)
{
	if (ctx->img.img_ptr)
		mlx_destroy_image(ctx->core, ctx->img.img_ptr);
	if (ctx->win)
		mlx_destroy_window(ctx->core, ctx->win);
	if (ctx->core)
		ft_free(ctx->core);
	return (NULL);
}

/**
 * Initialize an mlx context structure
 * @param fdf	A pointer to the main fdf structure
 * @return		Returns < 0 on error, 1 otherwise
 */
int	init_mlx_context(t_fdf *fdf)
{
	fdf->mlx = (t_mlx_ctx *)malloc(sizeof(t_mlx_ctx));
	if (!fdf->mlx)
		return (-1);
	fdf->mlx->res_w = RES_WIDTH;
	fdf->mlx->res_h = RES_HEIGHT;
	fdf->mlx->win = NULL;
	fdf->mlx->img.img_ptr = NULL;
	fdf->mlx->offset.x = RES_HEIGHT * 0.4;
	fdf->mlx->offset.y = RES_WIDTH * 0.5;
	fdf->mlx->rotation = degree_to_radians(30);
	fdf->mlx->max_rotation = degree_to_radians(MAX_ROTATION);
	fdf->mlx->core = mlx_init();
	if (!fdf->mlx->core)
		return (-2);
	create_img(fdf->mlx);
	if (!fdf->mlx->img.img_ptr)
		return (-3);
	return (1);
}

/**
 * Create and show a window
 * @param fdf		A pointer to the main fdf structure
 * @param win_title	The title of the window to create
 * @return			Returns 1 on success, -1 on error
 */
int	create_win(t_fdf *fdf, char *win_title)
{
	// TODO: make sure the max res is also used where RES_WIDTH and stuff is used
	catch_max_res_exception(fdf->mlx);
	fdf->mlx->win = mlx_new_window(fdf->mlx->core,
			fdf->mlx->res_w, fdf->mlx->res_h, win_title);
	if (!fdf->mlx->win)
		return (-1);
	return (0);
}
