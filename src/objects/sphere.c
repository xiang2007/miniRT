/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:41:46 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 10:42:46 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sp	*create_sphere(t_d x, t_d y, t_d z, t_d diameter)
{
	t_sp	*sphere;

	sphere = malloc(sizeof(t_sp));
	sphere = (t_sp *){0};
	sphere->x = x;
	sphere->y = y;
	sphere->z = z;
	sphere->diameter = diameter;
	sphere->next = NULL;
	return (sphere);
}

void	*set_sphere_color(t_sp *sphere, t_color *color)
{
	if (!sphere || !color)
		return (NULL);
	sphere->c = color;
}

void	*add_sphere_back(t_sp *src, t_sp *dest)
{
	if (!src || !dest)
		return (NULL);
	dest->next = src;
}