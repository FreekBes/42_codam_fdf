/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:54:47 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 19:14:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

void	init_fdf(t_fdf *fdf)
{
	fdf->map = NULL;
	fdf->mlx = NULL;
}

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
	}
}

static int	exit_hook(t_fdf *fdf)
{
	return (exit_fdf(fdf, 0, NULL, NULL));
}

void	setup_window(t_fdf *fdf, char *win_title)
{
	create_win(fdf, win_title);
	mlx_hook(fdf->mlx->win, 17, 1L << 17, &exit_hook, fdf);
	mlx_loop_hook(fdf->mlx->core, draw_next_frame, fdf);
	mlx_loop(fdf->mlx->core);
}
