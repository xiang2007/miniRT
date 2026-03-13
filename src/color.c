/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:32:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/12 16:21:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	create_color(double r, double g, double b)
{
	t_color	res;

	res.r = r;
	res.b = b;
	res.g = g;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	add_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r + b.r;
	res.g = a.g + b.g;
	res.b = a.b + b.b;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	mult_color(t_color a, t_color b)
{
	t_color	res;

	res.r = a.r * b.r;
	res.g = a.g * b.g;
	res.b = a.b * b.b;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}

t_color	mult_color_n(t_color c, double n)
{
	t_color	res;

	res.r = c.r * n;
	res.g = c.g * n;
	res.b = c.b * n;
	res.color = rgb_to_hex((int)(res.r * 255),
						(int)(res.g * 255),
						(int)(res.b * 255));
	return (res);
}
