/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:26:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 17:23:52 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define DEFAULT_COLOR 0x00FFFFFF
# define DEFAULT_TILE_SIZE_FACTOR 30
# define DEFAULT_relief_factor 0.5
# define RES_WIDTH 800
# define RES_HEIGHT 500

# define KEY_ZERO 29
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_EQUALS 24
# define KEY_MIN 27
# define KEY_SQ_BRACKET_L 33
# define KEY_SQ_BRACKET_R 30
# define KEY_ESC 53
# define BTN_MOUSE_L 1
# define BTN_MOUSE_R 2
# define BTN_SCROLL_UP 4
# define BTN_SCROLL_DOWN 5

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct s_col_rgba
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_col_rgba;

typedef struct s_gradient
{
	unsigned int	start;
	unsigned int	end;
}					t_gradient;

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
	t_coords		offset;
}					t_mlx_ctx;

typedef struct s_map
{
	unsigned int	default_color;
	double			tile_size;
	double			relief_factor;
	int				**map;
	t_coords		**iso_map;
	unsigned int	**colors;
	int				width;
	int				height;
}					t_map;

typedef struct s_keys_status
{
	int				left;
	int				right;
	int				up;
	int				down;
	int				plus;
	int				min;
	int				sq_br_l;
	int				sq_br_r;
}					t_keys_status;

typedef struct s_fdf
{
	t_keys_status	key_stat;
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
int					render_next_frame(t_fdf *fdf, int forced);
unsigned int		parse_hex(const char *s);
unsigned int		get_gradient_color(unsigned int color_s,
						unsigned int color_e, double perc);
int					is_off_screen(t_mlx_ctx *mlx, t_coords coords);
void				clear_img(t_mlx_ctx *mlx);
void				put_pixel(t_mlx_ctx *mlx, int h, int w, unsigned int c);
void				put_pixel_e(t_mlx_ctx *mlx, int h, int w, unsigned int c);
void				draw_line(t_mlx_ctx *mlx, t_coords start, t_coords *end,
						unsigned int c);
void				draw_line_g(t_mlx_ctx *mlx, t_coords start, t_coords *end,
						t_gradient *g);
void				cart_to_iso(const t_coords *cart, t_coords *iso);
void				iso_to_cart(const t_coords *iso, t_coords *cart);
void				reset_key_presses(t_keys_status *key_status);
void				handle_key_presses(t_fdf *fdf);
int					keypress(int keycode, t_fdf *fdf);
int					keyrelease(int keycode, t_fdf *fdf);
int					mousebtnpress(int btncode, int x, int y, t_fdf *fdf);
int					no_keys_pressed(t_keys_status *status);
void				reset_viewport(t_fdf *fdf);

#endif
