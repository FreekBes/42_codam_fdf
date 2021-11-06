/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_reader.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 18:54:45 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 19:59:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

static char	*append_buffer(char *contents, char *buff, size_t buff_size)
{
	static size_t	contents_size;
	static size_t	contents_len;
	char			*temp;

	if (!contents)
	{
		contents_size = buff_size + 1;
		contents = ft_calloc(contents_size, sizeof(char));
		contents_len = 0;
	}
	else
	{
		if (contents_len + buff_size >= contents_size)
		{
			contents_size *= 2;
			temp = ft_calloc(contents_size, sizeof(char));
			if (!temp)
				return (ft_free(contents));
			ft_memmove(temp, contents, contents_len);
			ft_free(contents);
			contents = temp;
		}
	}
	if (!contents)
		return (NULL);
	ft_memmove(contents + contents_len, buff, buff_size);
	contents_len += buff_size;
	return (contents);
}

static int	init_conf_parser(char *conf_file, char **cont, int *fd, void **buff)
{
	*cont = NULL;
	if (!extension_valid(conf_file, ".fdf")
		&& !extension_valid(conf_file, ".FDF"))
		return (-30);
	*fd = open(conf_file, O_RDONLY);
	if (*fd < 0)
		return (-31);
	*buff = ft_calloc(sizeof(char), 5012);
	if (!*buff)
		return (-6);
	return (1);
}

static int	read_conf(int fd, void **buffer, char **contents, int *err)
{
	int		i;
	int		read_res;

	i = 0;
	read_res = read(fd, *buffer, 5011);
	while (read_res > 0)
	{
		*contents = append_buffer(*contents, *buffer, 5011);
		if (!*contents)
		{
			*err = -6;
			read_res = 1;
			break ;
		}
		ft_bzero(*buffer, 5011);
		read_res = read(fd, *buffer, 5011);
		i++;
	}
	return (read_res);
}

int	parse_conf(t_map *map, char *conf_file)
{
	int		err;
	int		fd;
	char	*contents;
	void	*buffer;
	int		read_res;

	err = init_conf_parser(conf_file, &contents, &fd, &buffer);
	if (err < 0)
		return (err);
	read_res = read_conf(fd, &buffer, &contents, &err);
	if (read_res == 0)
		err = conf_to_map(map, ft_split(contents, '\n'));
	else if (read_res < 0)
		err = -33;
	ft_free(contents);
	ft_free(buffer);
	close(fd);
	return (err);
}
