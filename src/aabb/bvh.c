/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:55:07 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/31 14:33:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include "ray.h"
#include <stdlib.h>

int	bvh_size(t_objects **obj)
{
	int			size;
	t_objects	*o;

	if (!obj || !*obj)
		return (-1);
	o = *obj;
	size = 0;
	while (o)
	{
		if (o->type == OBJ_SPHERE || o->type == OBJ_CYLINDER)
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
		return (free_bvh(node), NULL);
	node->box = surround_box(node->left->box, node->right->box);
	return (node);
}

static bool	hit_bvh_leaf(t_bvh *node, t_bvh_args args)
{
	if (node->o == args.skip)
		return (false);
	if (node->o->type == OBJ_SPHERE
		&& hit_sphere(&node->o->sphere, args.ray,
			args.max_t, args.rec) > 0)
	{
		args.rec->hit_obj = node->o;
		return (true);
	}
	if (node->o->type == OBJ_CYLINDER && hit_cylinder(&node->o->cylinder,
			args.ray, args.max_t, args.rec) > 0)
	{
		args.rec->hit_obj = node->o;
		return (true);
	}
	if (node->o->type == OBJ_CONE && hit_cone(&node->o->cone, args.ray,
			args.max_t, args.rec) >0)
	{
		args.rec->hit_obj = node->o;
		return (true);
	}
	return (false);
}

bool	hit_bvh(t_bvh *node, t_bvh_args args)
{
	bool	hit_left;
	bool	hit_right;

	if (!node || !args.ray || !args.rec)
		return (false);
	if (!node->o && (!node->left || !node->right))
		return (false);
	if (!aabb_hit(&node->box, args.ray, 0.001, args.max_t))
		return (false);
	if (!node->left && !node->right)
		return (hit_bvh_leaf(node, args));
	hit_left = hit_bvh(node->left, args);
	if (hit_left)
		args.max_t = args.rec->t;
	hit_right = hit_bvh(node->right, args);
	return (hit_left || hit_right);
}
