/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 13:02:09 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/12 22:13:42 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/mlx_dat.h"
#include "../includes/minirt.h"
#include "../includes/parse.h"
#include <X11/keysym.h>
#include <stdio.h>

t_objects *select_object(int key, t_world *world)
{
	int			id;
	int			i;
	t_objects	*obj;
	t_objects	*temp;
	const int	keys[] = {XK_0, XK_1, XK_2, XK_3, XK_4, XK_5,
			XK_6, XK_7, XK_8, XK_9};

	obj = (world)->objs;
	i = 0;
	while(keys[i])
	{
		if (keys[i] == key)
			id = i;
		i++;
	}
	temp = obj;
	while(temp)
	{
		if (temp->id == id)
			return (print_object(obj), printf("id: %d %s\n", id, "selected"), temp);
		temp = temp->next;
	}
	return ((void *)0);
}

void move_obj_switch(int key, t_obj_type type, t_objects *o)
{
	if (type == OBJ_SPHERE)
		sphere_mv(key, o);
	return ;
}

void move_objects(int key, t_objects **obj)
{
	print_object((*obj));
	if (key >= XK_Left && key <= XK_Down)
		move_obj_switch(key, (*obj)->type, (*obj));
	return ;
}
