/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:59:56 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 11:04:24 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane(t_d x, t_d y, t_d z, t_color *c)
{
	t_plane	*plane;
	t_tuple	*t;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->x = x;
	plane->y = y;
	plane->z = z;
	t = create_point(x, y, z);
	plane->norm = normalize(t);
	free(t);
	plane->next = NULL;
	return (plane);
}

void	add_plane_next(t_plane *src, t_plane *dest)
{
	if (!src || !dest)
		return ;
	dest->next = src;
}
