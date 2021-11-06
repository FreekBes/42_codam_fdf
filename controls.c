/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 21:52:32 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 21:06:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fdf.h"
#include <stdio.h>

void	reset_key_presses(t_keys_status *key_status)
{
	key_status->left = 0;
	key_status->right = 0;
	key_status->up = 0;
	key_status->down = 0;
}

void	handle_key_presses(t_fdf *fdf)
{
	double	move_dir_up_down;
	double	move_dir_left_right;

	move_dir_up_down = 0;
	move_dir_left_right = 0;
	if (fdf->key_stat.up)
		move_dir_up_down += fdf->map->tile_size;
	if (fdf->key_stat.down)
		move_dir_up_down -= fdf->map->tile_size;
	if (fdf->key_stat.left)
		move_dir_left_right += fdf->map->tile_size;
	if (fdf->key_stat.right)
		move_dir_left_right -= fdf->map->tile_size;
	fdf->mlx->offset.y += move_dir_left_right;
	fdf->mlx->offset.x += move_dir_up_down;
}

int	keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		exit_fdf(fdf, 0, NULL, NULL);
	else if (keycode == KEY_LEFT)
		fdf->key_stat.left = 1;
	else if (keycode == KEY_RIGHT)
		fdf->key_stat.right = 1;
	else if (keycode == KEY_DOWN)
		fdf->key_stat.down = 1;
	else if (keycode == KEY_UP)
		fdf->key_stat.up = 1;
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
	render_next_frame(fdf, 1);
	return (1);
}

int	mousebtnpress(int btn_code, int x, int y, t_fdf *fdf)
{
	x = y;
	if (btn_code == BTN_MOUSE_L)
		fdf->map->translate_h += 0.05;
	else if (btn_code == BTN_MOUSE_R)
		fdf->map->translate_h -= 0.05;
	else if (btn_code == BTN_SCROLL_UP)
	{
		fdf->map->tile_size += 1;
		fdf->mlx->offset.x -= fdf->map->tile_size;
	}
	else if (btn_code == BTN_SCROLL_DOWN)
	{
		fdf->map->tile_size -= 1;
		fdf->mlx->offset.x += fdf->map->tile_size;
	}
	if (fdf->map->tile_size <= 0)
		fdf->map->tile_size = 1;
	return (1);
}

int	no_keys_pressed(t_keys_status *status)
{
	if (status->down || status->up || status->left || status->right)
		return (0);
	return (1);
}
