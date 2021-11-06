/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 16:24:41 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:38:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"

/**
 * Print an error to stderr
 * @param msg	The message to print
 */
static void	print_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (errno)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	ft_putchar_fd('\n', 2);
}

/** Exit the program
 * @param fdf		A pointer to the main fdf structure
 * @param exit_code	The exit code to use (EXIT_SUCCESS or EXIT_FAILURE)
 * @param error_msg	An error message to print, stack-allocated and non-freeable
 * @param alloc_msg	An error message to print, heap-allocated and freeable
 * @return			Returns exit_code
 */
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

/**
 * Get just the file name of a path
 * @param path	The path to get just the file name of
 * @return		A pointer to just the file name, non-freeable
*/
char	*get_file_name(char *path)
{
	char	*name;

	name = ft_strchr(path, '/');
	if (!name)
		name = path;
	else
		name += 1;
	return (name);
}

/**
 * The main, what can I say
 * @param argc	The amount of arguments in argv
 * @param argv	The arguments given to the program by the shell
 */
int	main(int argc, char **argv)
{
	t_fdf	fdf;
	char	*temp1;
	char	*temp2;

	errno = 0;
	init_fdf(&fdf);
	setup_args(argc, argv, &fdf);
	if (init_mlx_context(&fdf) < 0)
		exit_fdf(&fdf, EXIT_FAILURE, "Failed to initialize mlx library", NULL);
	temp1 = ft_strjoin(get_file_name(argv[1]), " - ");
	temp2 = ft_strjoin(temp1, get_file_name(argv[0]));
	setup_window(&fdf, temp2);
	free(temp1);
	free(temp2);
	exit_fdf(&fdf, EXIT_SUCCESS, NULL, NULL);
}
