/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:55:07 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/19 14:01:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <stddef.h>

t_bvh	*build_bvh(t_objects **objects, int start, int end)
{
	int		half;
	t_bvh	*node;

	node = malloc(sizeof(t_bvh));
	if (end - start == 1)
	{
		node->o = *objects[start];
		node->left = NULL;
		node->right = NULL;
		return (node);
	}
	half = (end - start)/2;
}