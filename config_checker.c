/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_checker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:59:25 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:13:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

/**
 * Check if a file name ends with a certain extension
 * @param file_name		The file name
 * @param ext			The expected extension
 * @return				Returns 1 if file name ends with extension, or 0 if not
 */
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
