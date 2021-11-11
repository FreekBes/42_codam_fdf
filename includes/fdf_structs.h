/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_structs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:30:07 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:51:47 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H

typedef struct s_coords
{
	int				x;
	int				y;
}					t_coords;

typedef struct s_zcoords
{
	int				x;
	int				y;
	int				z;
}					t_zcoords;

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
	double			rotation;
	double			max_rotation;
}					t_mlx_ctx;

typedef struct s_map
{
	unsigned int	default_color;
	double			tile_size;
	double			relief_factor;
	int				**alts;
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
	int				comma;
	int				dot;
}					t_keys_status;

typedef struct s_fdf
{
	t_keys_status	key_stat;
	t_mlx_ctx		*mlx;
	t_map			*map;
}					t_fdf;

#endif
