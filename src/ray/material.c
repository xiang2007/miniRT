/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:59:54 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 05:19:48 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "color.h"
#include "objects.h"
#include "vec3.h"
#include <stdbool.h>

bool	material_is_transparent(t_objects *o)
{
	t_material	*mat;

	mat = NULL;
	if (o->type == OBJ_SPHERE)
		mat = o->sphere.material;
	else if (o->type == OBJ_CYLINDER)
		mat = o->cylinder.material;
	else if (o->type == OBJ_PLANE)
		mat = o->plane.material;
	else if (o->type == OBJ_CONE)
		mat = o->cone.material;
	return (mat && mat->scatter == dielectric_scatter);
}

t_color	black_emit(const struct s_material *self)
{
	(void)self;
	return (create_color(0, 0, 0)); 
}

void	toggle_checker(t_objects *sel)
{
	t_lambertian	*lam;

	if (!sel || sel->type != OBJ_PLANE)
		return ;
	lam = (t_lambertian *)sel->plane.material;
	if (!lam || lam->base.scatter != lambertian_scatter)
		return ;
	if (lam->checker_size > 0.0)
		lam->checker_size = 0.0;
	else
	{
		lam->checker_size = 1.0;
		lam->checker_color = create_color(1.0, 1.0, 1.0);
	}
}