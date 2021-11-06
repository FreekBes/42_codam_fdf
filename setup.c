/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:54:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:32:42 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

/**
 * Initialize the main fdf structure
 * @param fdf	The main fdf structure
 */
void	init_fdf(t_fdf *fdf)
{
	fdf->map = NULL;
	fdf->mlx = NULL;
}

/**
 * Parse the arguments given to the program and handle them
 * @param argc	The amount of arguments given
 * @param argv	The arguments in a string array
 * @param fdf	A pointer to the main fdf structure
 */
void	setup_args(int argc, char **argv, t_fdf *fdf)
{
	int		err;

	if (argc > 2)
		exit_fdf(fdf, EXIT_FAILURE, "Too many arguments", NULL);
	else if (argc < 2)
		exit_fdf(fdf, EXIT_FAILURE, "Missing config file", NULL);
	else
	{
		fdf->map = init_map();
		if (!fdf->map)
			exit_fdf(fdf, EXIT_FAILURE, "Malloc for map failed", NULL);
		if (parse_conf(fdf->map, argv[1]) < 0)
			exit_fdf(fdf, EXIT_FAILURE, "Failed to load config", NULL);
		fdf->map->tile_size = RES_HEIGHT / fdf->map->height * 0.5;
		if (fdf->map->tile_size <= 0)
			fdf->map->tile_size = 1;
	}
}

/**
 * Method used to exit the program when ESC is pressed
 * @param fdf	A pointer to the main fdf structure
 * @return		Returns the value exit_fdf returns
 */
static int	exit_hook(t_fdf *fdf)
{
	return (exit_fdf(fdf, 0, NULL, NULL));
}

/**
 * Setup the window
 * @param fdf		A pointer to the main fdf structure
 * @param win_title	The title of the program
 */
void	setup_window(t_fdf *fdf, char *win_title)
{
	create_win(fdf, win_title);
	mlx_hook(fdf->mlx->win, 17, 1L << 17, &exit_hook, fdf);
	mlx_hook(fdf->mlx->win, 2, 1L << 0, &keypress, fdf);
	mlx_hook(fdf->mlx->win, 3, 1L << 1, &keyrelease, fdf);
	mlx_loop_hook(fdf->mlx->core, draw_next_frame, fdf);
	mlx_loop(fdf->mlx->core);
}
