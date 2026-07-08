/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:32:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/06/11 02:44:00 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include "../../includes/color.h"

/**
 * @brief Creates a colour struct filled with rgb parameter
 *
 * @param r the red
 * @param g the green
 * @param b the blue
 * @return the new colour struct
 */
t_color	create_color(double r, double g, double b)
{
	t_color	res;

	res.r = r;
	res.b = b;
	res.g = g;
	return (res);
}

/**
 * @brief Add colour
 *
 * @param a the first colour
 * @param b the second colour
 * @return the new colour
 */
t_color	color_add(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

/**
 * @brief Multiply colours
 *
 * @param a the first colour
 * @param b the second colour
 * @return the new colour
 */
t_color	color_mul(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

/**
 * @brief Multiply colour with a scalar number
 *
 * @param c the colour
 * @param n the scalar value
 * @return the new colour
 */
t_color	color_mul_n(t_color c, double n)
{
	t_color	res;

	res.r = c.r * n;
	res.g = c.g * n;
	res.b = c.b * n;
	return (res);
}

/**
 * @brief Calculates the hex value of the colour
 *
 * @param c the colour
 * @return the hex value in integer
 */
int	color_get_hex(t_color c)
{
	return (rgb_to_hex((int)(c.r * 255), (int)(c.g * 255), (int)(c.b * 255)));
}
