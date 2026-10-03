/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:45:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/31 16:28:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "aabb.h"
#include "material.h"
#include "objects.h"
#include "ray.h"
#include <math.h>

void	build_box_switch(t_objects *o)
{
	if (o && (o->type == OBJ_SPHERE || o->type == OBJ_CYLINDER
			|| o->type == OBJ_CONE))
		o->box = build_box(o);
}

/**
 * @brief Adds the object to the back of the 'dest' struct
 *
 * @param src node to append to the back
 * @param dest linked list
 */
void	obj_add_back(t_objects *src, t_objects **dest)
{
	t_objects	*ptr;

	if (!dest || !src)
		return ;
	if (!*dest)
	{
		*dest = src;
		src->next = NULL;
		return ;
	}
	ptr = *dest;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = src;
	src->next = NULL;
}

t_objects	**obj2arr(t_objects *o)
{
	int			size;
	int			i;
	t_objects	**res;
	t_objects	*head;

	if (!o)
		return (NULL);
	head = o;
	size = obj_bvh_count(o);
	res = malloc(sizeof(t_objects *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->type == OBJ_SPHERE || head->type == OBJ_CYLINDER
			|| head->type == OBJ_CONE)
			res[i++] = head;
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}

void	set_face_normal(const t_ray *r, const t_vec3 *out_norm, t_hit_dat *rec)
{
	rec->front_face = vec3_dot(r->vec, *out_norm) < 0.001;
	if (rec->front_face)
		rec->normal = *out_norm;
	else
		rec->normal = vec3_mul(*out_norm, -1.0);
}

double	bump_height(double u, double v)
{
	return (0.5 * (1.0 + sin(u * 50.0) * cos(v * 50.0)));
}
