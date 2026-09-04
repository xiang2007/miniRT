/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:37:21 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 17:56:16 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "../../includes/parse.h"
#include "../../includes/aabb.h"

// static t_objects	*parse_create_object(t_objects *o)
// {
// 	if (o->type == OBJ_AMBIENT)
// 		return (create_object(&o->ambient, o->type, o->id));
// 	if (o->type == OBJ_SPHERE)
// 		return (create_object(&o->sphere, o->type, o->id));
// 	if (o->type == OBJ_PLANE)
// 		return (create_object(&o->plane, o->type, o->id));
// 	if (o->type == OBJ_CYLINDER)
// 		return (create_object(&o->cylinder, o->type, o->id));
// 	if (o->type == OBJ_LIGHT)
// 		return (create_object(&o->light, o->type, o->id));
// 	if (o->type == OBJ_CONE)
// 		return (create_object(&o->cone, o->type, o->id));
// 	return (NULL);
// }

/**
 * @brief Iterates through the t_objects linked list and adds it to the
 * t_world struct
 *
 * @param w world struct
 * @param o object linked list
 */
void	parse_world(t_world *w, t_objects **o)
{
	t_objects	*p;
	t_objects	*tmp;
	int			count;

	if (!w || !o)
		return ;
	w->bvh_obj = NULL;
	w->bvh = NULL;
	p = *o;
	while (p)
	{
		tmp = p->next;
		if (p->type == OBJ_SETUP_CAM || p->type == OBJ_CAMERA)
			free(p);
		else
			world_add_back(w, p, p->type);
		p = tmp;
	}
	*o = NULL;
	w->bvh_obj = obj2arr(w->objs);
	count = obj_bvh_count(w->objs);
	if (w->bvh_obj && count > 0)
		w->bvh = build_bvh(w->bvh_obj, 0, count);
}

t_parse	parse_object_count(t_objects *o)
{
	t_parse		c;
	t_objects	*p;

	p = o;
	ft_memset(&c, 0, sizeof(t_parse));
	while (p)
	{
		if (p->type == OBJ_AMBIENT)
			c.ambient++;
		else if (p->type == OBJ_LIGHT)
			c.light++;
		else if (p->type == OBJ_CYLINDER)
			c.cylinder++;
		else if (p->type == OBJ_PLANE)
			c.plane++;
		else if (p->type == OBJ_SPHERE)
			c.sphere++;
		else if (p->type == OBJ_SETUP_CAM)
			c.camera++;
		else if (p->type == OBJ_CONE)
			c.cone++;
		p = p->next;
	}
	c.object = c.ambient + c.light + c.cylinder + c.sphere + c.cone;
	return (c);
}

int	parse_check_object_count(t_objects *o)
{
	t_parse	p;
	int		total;

	p = parse_object_count(o);
	total = p.ambient + p.camera + p.cylinder + p.light + p.plane + p.sphere
		+ p.cone;
	if (total < 1)
		return (FALSE);
	if (p.object < 1)
		return (FALSE);
	if (p.camera < 1 || p.camera > 1)
		return (FALSE);
	if (p.ambient < 1)
		return (FALSE);
	if (p.light < 1)
		return (FALSE);
	return (TRUE);
}

t_objects	*parse(char *file)
{
	int			fd;
	t_objects	*o;

	if (check_rt_file(file) == FALSE)
		return (NULL);
	fd = read_rt_file(file);
	if (fd == -1)
		return (NULL);
	o = parse_object(fd);
	if (!parse_check_object_count(o))
		return (parse_free_objects(o), NULL);
	return (o);
}
