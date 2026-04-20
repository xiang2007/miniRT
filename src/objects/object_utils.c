/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:45:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/21 00:54:07 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
	while(ptr->next)
		ptr = ptr->next;
	ptr->next = src;
	src->next = NULL;
}

t_objects	*create_object(void *obj, t_obj_type type)
{
	t_objects	*res;

	res = malloc(sizeof(t_objects));
	if (!res)
		return (NULL);
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
	return (res);
}
