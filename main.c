/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:24:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 23:07:06 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"

static void	print_error(char *msg)
{
	ft_putendl_fd("Error", 1);
	if (msg)
		ft_putstr_fd(msg, 1);
	if (errno)
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
	}
	ft_putchar_fd('\n', 1);
}

int	exit_fdf(t_fdf *fdf, int exit_code, char *error_msg, char *alloc_msg)
{
	if (error_msg)
		print_error(error_msg);
	if (alloc_msg)
	{
		print_error(alloc_msg);
		ft_free(alloc_msg);
	}
	if (fdf->mlx)
		free_mlx_context(fdf->mlx);
	if (fdf->map)
		free_map(fdf->map);
	exit(exit_code);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	errno = 0;
	init_fdf(&fdf);
	setup_args(argc, argv, &fdf);
	if (init_mlx_context(&fdf) < 0)
		exit_fdf(&fdf, EXIT_FAILURE, "Failed to initialize mlx library", NULL);
	setup_window(&fdf, argv[0]);
	exit_fdf(&fdf, EXIT_SUCCESS, NULL, NULL);
}
