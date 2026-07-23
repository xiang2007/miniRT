/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:45:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/23 17:09:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/aabb.h"

void	build_box_switch(t_objects *o)
{
	if (o && o->type == OBJ_SPHERE)
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

/**
 * @brief Creates object struct and assigns the type with the obj data
 *
 * @param obj the object data
 * @param type the object type
 * @return the node or NULL if malloc fail
 */
t_objects	*create_object(void *obj, t_obj_type type, int id)
{
	t_objects	*res;

	res = malloc(sizeof(t_objects));
	if (!res)
		return (NULL);
	res->id = id;
	res->type = type;
	res->next = NULL;
	if (type == OBJ_SPHERE)
		res->sphere = *(t_sphere *)obj;
	else if (type == OBJ_AMBIENT)
		res->ambient = *(t_ambient *)obj;
	else if (type == OBJ_CYLINDER)
		res->cylinder = *(t_cylinder *)obj;
	else if (type == OBJ_PLANE)
		res->plane = *(t_plane *)obj;
	else if (type == OBJ_LIGHT)
		res->light = *(t_light *)obj;
	build_box_switch(res);
	return (res);
}

/**
 * @brief Prints the name of all the objects in the linked list
 *
 * @param o the linked list
 */
void	print_object_list(t_objects *o)
{
	const char	*t[7] = {"AMBIENT", "CAMERA", "SPHERE", "PLANE",
		"CYLINDER", "LIGHT", "S_CAM"};
	t_objects	*p;

	if (!o)
		return ;
	p = o;
	while (p)
	{
		printf("Object: %s\n", t[p->type]);
		p = p->next;
	}
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
	size = obj_sphere_count(o);
	res = malloc(sizeof(t_objects *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (head)
	{
		if (head->type == OBJ_SPHERE)
			res[i++] = head;
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}
