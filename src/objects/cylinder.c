/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:04:35 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 23:39:40 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_d x, t_d y, t_d z)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->x = x;
	cylinder->y = y;
	cylinder->z = z;
	
}

void	set_cylinder_argument(t_cylinder *cy, t_d diameter, t_d height, t_color *c)
{
	if (!cy)
		return ;
	if (diameter)
		cy->dia	= diameter;
	if (height)
		cy->height = height;
	if (c)
		cy->c = c;
	return ;
}