/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:55:07 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 20:18:46 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include "ray.h"
#include <stddef.h>
#include <stdlib.h>

int	bvh_size(t_objects **obj)
{
	int			size;
	t_objects	*o;

	if (!obj || !*obj)
		return (-1);
	o = *obj;
	size = 0;
	while(o)
	{
		if (o->type == OBJ_SPHERE)
			size++;
		o = o->next;
	}
	return (size);
}

void	free_bvh(t_bvh *node)
{
	if (!node)
		return ;
	free_bvh(node->left);
	free_bvh(node->right);
	free(node);
}

t_bvh	*build_bvh(t_objects **objects, int start, int end)
{
	int		half;
	t_bvh	*node;

	if (!objects || start >= end)
		return (NULL);
	node = malloc(sizeof(t_bvh));
	if (!node)
		return (NULL);
	node->o = NULL;
	if (end - start == 1)
	{
		node->o = objects[start];
		node->left = NULL;
		node->right = NULL;
		node->box = build_box(objects[start]);
		return (node);
	}
	half = (end - start) / 2;
	node->left = build_bvh(objects, start, start + half);
	node->right = build_bvh(objects, start + half, end);
	if (!node->left || !node->right)
		return(free_bvh(node), NULL);
	node->box = surround_box(node->left->box, node->right->box);
	return (node);
}

bool	hit_bvh(t_bvh *node, t_ray *ray, double max_t, t_hit_dat *rec)
{
	bool	hit_left;
	bool	hit_right;
	double	closest_so_far;

	closest_so_far = INFINITY;
	if (!node || !ray || !rec)
		return (false);
	if (!node->o && (!node->left || !node->right))
		return (false);
	if (!aabb_hit(&node->box, ray, 0.001, max_t))
		return (false);
	if (!node->left && !node->right)
	{
		if (node->o->type == OBJ_SPHERE)
			return (hit_sphere(&node->o->sphere, ray, max_t, rec) > 0);
		return (false);
	}
	closest_so_far = max_t;
	hit_left = hit_bvh(node->left, ray, closest_so_far, rec);
	if (hit_left)
		closest_so_far = rec->t;
	hit_right = hit_bvh(node->right, ray, closest_so_far, rec);
	return (hit_left || hit_right);
}
