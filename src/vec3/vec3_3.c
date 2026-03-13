/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:36:32 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/12 15:27:59 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	create_vec3(double a, double b, double c)
{
	t_vec3	res;

	res.x = a;
	res.y = b;
	res.z = c;
	return (res);
}

t_vec3	mult_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}
