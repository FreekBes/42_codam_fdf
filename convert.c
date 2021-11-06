/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/05 20:16:52 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/06 22:21:27 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Convert default coordinates to isometric coordinates
 * @param cart	A pointer to the default coordinates struct
 * @param iso	A pointer to the isometric coordinates struct
 */
void	cart_to_iso(const t_coords *cart, t_coords *iso)
{
	iso->x = cart->x - cart->y;
	iso->y = (cart->x + cart->y) / 2;
}

/**
 * Convert isometric coordinates to default coordinates
 * @param iso	A pointer to the isometric coordinates struct
 * @param cart	A pointer to the default coordinates struct
 */
void	iso_to_cart(const t_coords *iso, t_coords *cart)
{
	cart->x = (2 * iso->y + iso->x) / 2;
	cart->y = (2 * iso->y - iso->x) / 2;
}
