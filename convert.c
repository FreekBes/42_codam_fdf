/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 20:16:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/08 18:03:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

/**
 * Convert degrees to radians
 * @param degree	The degree to convert
 * @return			The degree as a radian
 */
float	degree_to_radians(int degree)
{
	if (degree < 0)
		degree = 360;
	else if (degree > 360)
		degree = 0;
	return (degree * M_PI / 180);
}
