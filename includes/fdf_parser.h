/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_parser.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:33:30 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:35:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_PARSER_H
# define FDF_PARSER_H

# include "fdf.h"

t_map			*init_map(void);
int				parse_conf(t_map *map, char *conf_file);
int				conf_to_map(t_map *map, char **conf);
void			*free_map(t_map *map);
void			setup_args(int argc, char **argv, t_fdf *fdf);
int				extension_valid(char *file_name, char *ext);
unsigned int	parse_hex(const char *s);
void			print_map(t_map *map);

#endif
