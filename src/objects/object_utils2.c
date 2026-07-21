/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 00:33:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 20:26:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	obj_size(t_objects *o)
{
	t_objects	*t;
	int			size;

	size = 0;
	if (!o)
		return (-1);
	t = o;
	while(t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

int	obj_sphere_count(t_objects *o)
{
	int			size;
	t_objects	*t;

	if (!o)
		return (-1);
	t = o;
	size = 0;
	while(t)
	{
		if (t->type == OBJ_SPHERE)
			size++;
		t = t->next;
	}
	return (size);
}