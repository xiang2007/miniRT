/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:55:07 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/20 09:23:27 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <stddef.h>
#include <stdlib.h>

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

	node = malloc(sizeof(t_bvh));
	if (end - start == 1)
	{
		node->o = objects[start];
		node->left = NULL;
		node->right = NULL;
		node->box = build_box(objects[start]);
		return (node);
	}
	half = (end - start)/2;
	node->left = build_bvh(objects, start, half);
	node->right = build_bvh(objects, half, end);
	node->box = surround_box(node->left->box, node->right->box);
	return (node);
}