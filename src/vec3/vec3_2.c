/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:40:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 17:57:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	len_sq(t_vec3 a)
{
	return (sq(a.x) + sq(a.y) + sq(a.z));
}

double	len_vec(t_vec3 a)
{
	return (sqrt(len_sq(a)));
}

t_vec3	cross_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	dot_vec(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	unit_vec(t_vec3 a)
{
	return (div_vec(a, len_vec(a)));
}
