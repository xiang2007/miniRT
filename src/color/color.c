/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:32:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 15:20:41 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "color.h"

t_color	create_color(double r, double g, double b)
{
	t_color	res;

	res.r = r;
	res.b = b;
	res.g = g;
	return (res);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	return (res);
}

t_color	color_mul(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	return (res);
}

t_color	color_mul_n(t_color c, double n)
{
	t_color	res;

	res.r = c.r * n;
	res.g = c.g * n;
	res.b = c.b * n;
	return (res);
}

int	color_get_hex(t_color c)
{
	return (rgb_to_hex((int)(c.r * 255), (int)(c.g * 255), (int)(c.b * 255)));
}
