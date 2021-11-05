/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_checker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:59:25 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 18:59:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

int	extension_valid(char *file_name, char *ext)
{
	size_t		filename_len;
	size_t		ext_len;

	filename_len = ft_strlen(file_name);
	ext_len = ft_strlen(ext);
	if (filename_len < ext_len)
		return (0);
	if (ft_strncmp(file_name + filename_len - ext_len, ext, ext_len) != 0)
		return (0);
	return (1);
}
