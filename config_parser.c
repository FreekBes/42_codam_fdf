/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 19:02:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/05 19:37:56 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int	get_split_size(char **values)
{
	int			i;

	i = 0;
	while (values[i] && ft_strlen(values[i]) > 0)
		i++;
	return (i);
}

int	conf_to_map(t_map *map, char **conf)
{
	int			err;
	int			i;
	int			j;
	char		**values;

	if (!conf)
		return (-1);
	err = 0;
	i = 0;
	map->height = get_split_size(conf);
	map->map = (int **)ft_calloc(map->height, sizeof(int *));
	while (conf[i] && err >= 0)
	{
		if (ft_strlen(conf[i]) > 0)
		{
			values = ft_split(conf[i], ' ');
			if (!values)
				err = -1;
			if (map->width == 0)
				map->width = get_split_size(values);
			else if (get_split_size(values) != map->width)
			{
				err = -2;
				break ;
			}
			map->map[i] = (int *)ft_calloc(map->width, sizeof(int));
			j = 0;
			while (values[j])
			{
				map->map[i][j] = ft_atoi(values[j]);
				j++;
			}
			ft_free_double_ptr((void **)values);
		}
		else
			err = -3;
		i++;
	}
	ft_free_double_ptr((void **)conf);
	print_map(map);
	return (err);
}
