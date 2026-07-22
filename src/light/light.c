/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:12:35 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/22 14:43:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/ray.h"
#include "../includes/mlx_dat.h"
#include "../includes/objects.h"
#include "../includes/color.h"
#include <stddef.h>

t_light	*get_light(t_world *w)
{
	t_objects	*t;

	if (!w)
		return (NULL);
	t = w->objs;
	while(t)
	{
		if(t->type == OBJ_LIGHT)
			return (&t->light);
		t = t->next;
	}
	return (NULL);
}


