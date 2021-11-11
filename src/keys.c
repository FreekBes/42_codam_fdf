/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 16:45:26 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:43:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "fdf.h"
#include "fdf_drawer.h"

/**
 * Reset the pressed keys
 * @param keys_status	The struct containing key statuses
 */
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
	key_status->comma = 0;
	key_status->dot = 0;
}

/**
 * Let the program know a keyboard key has been pressed
 * @param keycode	The keycode of the pressed key
 * @param fdf		The main fdf struct
 * @return			Always returns 1
 */
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
	else if (keycode == KEY_COMMA)
		fdf->key_stat.comma = 1;
	else if (keycode == KEY_DOT)
		fdf->key_stat.dot = 1;
	return (1);
}

/**
 * Let the program know a keyboard key has been released
 * @param keycode	The keycode of the released key
 * @param fdf		The main fdf struct
 * @return			Always returns 1
 */
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
	else if (keycode == KEY_COMMA)
		fdf->key_stat.comma = 0;
	else if (keycode == KEY_DOT)
		fdf->key_stat.dot = 0;
	render_next_frame(fdf, 1);
	return (1);
}

/**
 * Check if there are currently no keyboard keys pressed
 * @param status	The struct containing key statuses
 * @return			An integer, 1 if there are keys being pressed, 0 if not
 */
int	no_keys_pressed(t_keys_status *status)
{
	if (status->down || status->up || status->left || status->right
		|| status->min || status->plus || status->sq_br_l || status->sq_br_r
		|| status->comma || status->dot)
		return (0);
	return (1);
}
