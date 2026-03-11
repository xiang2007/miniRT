/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:41:46 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 16:11:49 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sp	*create_sphere(t_tuple *origin, t_d diameter)
{
	t_sp	*sphere;
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		return (NULL);
	ft_memset(sphere, 0, sizeof(t_sp));
	sphere->origin = origin;
	sphere->diameter = diameter;
	sphere->transform = create_transformation_matrix();
	sphere->c = NULL;
	sphere->next = NULL;
	return (sphere);
}

void	set_sphere_color(t_sp *sphere, t_color *color)
{
	if (!sphere || !color)
		return ;
	sphere->c = color;
}

void	add_sphere_back(t_sp *src, t_sp **dest)
{
	if (!src || !dest)
		return ;
	(*dest)->next = src;
}

void	print_sphere(t_sp *s)
{
	printf("x: %f y: %f z: %f d: %f\n", s->origin->x, s->origin->y,
			s->origin->z, s->diameter);
}
