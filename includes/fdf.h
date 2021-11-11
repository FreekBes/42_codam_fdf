/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:26:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:35:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_structs.h"

# define U_INT unsigned int
# define KEY_ZERO 29
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_EQUALS 24
# define KEY_MIN 27
# define KEY_SQ_BRACKET_L 33
# define KEY_SQ_BRACKET_R 30
# define KEY_COMMA 43
# define KEY_DOT 47
# define KEY_ESC 53

int		exit_fdf(t_fdf *fdf, int exit_code, char *error_msg,
			char *alloc_msg);
void	init_fdf(t_fdf *fdf);
int		init_mlx_context(t_fdf *fdf);
void	*free_mlx_context(t_mlx_ctx *ctx);
int		create_win(t_fdf *fdf, char *win_title);
void	setup_window(t_fdf *fdf, char *win_title);
double	degree_to_radians(int degree);
void	rotate(int degree, t_zcoords *coords, t_zcoords *rcoords);
void	reset_key_presses(t_keys_status *key_status);
void	handle_key_presses(t_fdf *fdf);
int		keypress(int keycode, t_fdf *fdf);
int		keyrelease(int keycode, t_fdf *fdf);
int		mousebtnpress(int btncode, int x, int y, t_fdf *fdf);
int		no_keys_pressed(t_keys_status *status);
void	reset_viewport(t_fdf *fdf);

#endif
