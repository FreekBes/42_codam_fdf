/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:26:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 19:36:25 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define DEFAULT_COLOR 0xFFFFFF
# define RES_WIDTH 1280
# define RES_HEIGHT 720

typedef struct s_img
{
	char			*img_ptr;
	char			*address;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
}					t_img;

typedef struct s_mlx_ctx
{
	void			*core;
	void			*win;
	unsigned int	res_w;
	unsigned int	res_h;
	t_img			img;
}					t_mlx_ctx;

typedef struct s_map
{
	unsigned int	default_color;
	int				**map;
	unsigned int	**colors;
	int				width;
	int				height;
}					t_map;

typedef struct s_fdf
{
	t_mlx_ctx		*mlx;
	t_map			*map;
}					t_fdf;

int					exit_fdf(t_fdf *fdf, int exit_code, char *error_msg,
						char *alloc_msg);
void				init_fdf(t_fdf *fdf);
int					init_mlx_context(t_fdf *fdf);
void				*free_mlx_context(t_mlx_ctx *ctx);
int					create_win(t_fdf *fdf, char *win_title);
t_map				*init_map(void);
int					parse_conf(t_map *map, char *conf_file);
int					conf_to_map(t_map *map, char **conf);
void				*free_map(t_map *map);
void				setup_args(int argc, char **argv, t_fdf *fdf);
void				setup_window(t_fdf *fdf, char *win_title);
int					draw_next_frame(t_fdf *fdf);
int					extension_valid(char *file_name, char *ext);
void				print_map(t_map *map);

#endif
