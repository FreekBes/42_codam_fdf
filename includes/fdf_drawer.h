/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_drawer.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:32:13 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:35:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DRAWER_H
# define FDF_DRAWER_H

# include "fdf.h"

int				check_if_recalc_needed(t_fdf *fdf);
int				check_if_redraw_needed(t_fdf *fdf);
int				draw_next_frame(t_fdf *fdf);
int				render_next_frame(t_fdf *fdf, int forced);
unsigned int	get_gradient_color(unsigned int color_s,
					unsigned int color_e, double perc);
int				is_off_screen(t_mlx_ctx *mlx, t_coords coords);
void			clear_img(t_mlx_ctx *mlx);
void			put_pixel(t_mlx_ctx *mlx, int h, int w, unsigned int c);
void			draw_line(t_mlx_ctx *mlx, t_coords start, t_coords *end,
					unsigned int c);
void			draw_line_g(t_mlx_ctx *mlx, t_coords start, t_coords *end,
					t_gradient *g);

#endif
