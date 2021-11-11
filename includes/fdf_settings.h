/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_settings.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 18:30:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/11 18:51:17 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_SETTINGS_H
# define FDF_SETTINGS_H

/* The default color for lines and points */
# define DEFAULT_COLOR 0x00FFFFFF

/* The default factor for the relief, higher value = more relief */
# define DEFAULT_RELIEF_FACTOR 0.5

/* The window width */
# define RES_WIDTH 1600

/* The window height */
# define RES_HEIGHT 900

/* Always draw lines, even on keypresses */
# define ALWAYS_DRAW_LINES 0

/* The maximum rotation to be applied with the dot and comma keys */
# define MAX_ROTATION 45

#endif
