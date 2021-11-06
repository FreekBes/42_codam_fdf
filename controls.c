/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 21:52:32 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:09:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fdf.h"
#	include	<stdio.h>

void	reset_key_presses(t_keys_status *key_status)
{
	key_status->left = 0;
	key_status->right = 0;
	key_status->up = 0;
	key_status->down = 0;
	key_status->min = 0;
	key_status->plus = 0;
	key_status->sq_br_l = 0;
	key_status->sq_br_r = 0;
}

void	handle_key_presses(t_fdf *fdf)
{
	int		move_dir_up_down;
	int		move_dir_left_right;
	double	zoom;
	double	relief;

	move_dir_up_down = 0;
	move_dir_left_right = 0;
	zoom = 1;
	relief = 0;
	if (fdf->key_stat.up)
		move_dir_up_down += 1 + fdf->map->tile_size * 0.2;
	if (fdf->key_stat.down)
		move_dir_up_down -= 1 + fdf->map->tile_size * 0.2;
	if (fdf->key_stat.left)
		move_dir_left_right += 1 + fdf->map->tile_size * 0.2;
	if (fdf->key_stat.right)
		move_dir_left_right -= 1 + fdf->map->tile_size * 0.2;
	if (fdf->key_stat.min)
		zoom -= 0.1;
	if (fdf->key_stat.plus)
		zoom += 0.1;
	if (fdf->key_stat.sq_br_l)
		relief -= 0.01;
	if (fdf->key_stat.sq_br_r)
		relief += 0.01;
	fdf->mlx->offset.y += move_dir_left_right;
	fdf->mlx->offset.x += move_dir_up_down;
	fdf->map->tile_size *= zoom;
	if (fdf->map->tile_size < 1)
		fdf->map->tile_size = 1;
	fdf->map->relief_factor += relief;
}

int	keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		exit_fdf(fdf, 0, NULL, NULL);
	else if (keycode == KEY_ZERO)
		reset_viewport(fdf);
	else if (keycode == KEY_LEFT)
		fdf->key_stat.left = 1;
	else if (keycode == KEY_RIGHT)
		fdf->key_stat.right = 1;
	else if (keycode == KEY_UP)
		fdf->key_stat.up = 1;
	else if (keycode == KEY_DOWN)
		fdf->key_stat.down = 1;
	else if (keycode == KEY_EQUALS)
		fdf->key_stat.plus = 1;
	else if (keycode == KEY_MIN)
		fdf->key_stat.min = 1;
	else if (keycode == KEY_SQ_BRACKET_L)
		fdf->key_stat.sq_br_l = 1;
	else if (keycode == KEY_SQ_BRACKET_R)
		fdf->key_stat.sq_br_r = 1;
	return (1);
}

int	keyrelease(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_LEFT)
		fdf->key_stat.left = 0;
	else if (keycode == KEY_RIGHT)
		fdf->key_stat.right = 0;
	if (keycode == KEY_UP)
		fdf->key_stat.up = 0;
	else if (keycode == KEY_DOWN)
		fdf->key_stat.down = 0;
	else if (keycode == KEY_EQUALS)
		fdf->key_stat.plus = 0;
	else if (keycode == KEY_MIN)
		fdf->key_stat.min = 0;
	else if (keycode == KEY_SQ_BRACKET_L)
		fdf->key_stat.sq_br_l = 0;
	else if (keycode == KEY_SQ_BRACKET_R)
		fdf->key_stat.sq_br_r = 0;
	render_next_frame(fdf, 1);
	return (1);
}

int	no_keys_pressed(t_keys_status *status)
{
	if (status->down || status->up || status->left || status->right
		|| status->min || status->plus || status->sq_br_l || status->sq_br_r)
		return (0);
	return (1);
}
