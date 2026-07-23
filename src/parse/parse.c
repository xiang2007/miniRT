/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:37:21 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/23 17:09:39 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/aabb.h"

static t_objects	*parse_create_object(t_objects *o)
{
	if (o->type == OBJ_AMBIENT)
		return (create_object(&o->ambient, o->type, o->id));
	if (o->type == OBJ_SPHERE)
		return (create_object(&o->sphere, o->type, o->id));
	if (o->type == OBJ_PLANE)
		return (create_object(&o->plane, o->type, o->id));
	if (o->type == OBJ_CYLINDER)
		return (create_object(&o->cylinder, o->type, o->id));
	if (o->type == OBJ_LIGHT)
		return (create_object(&o->light, o->type, o->id));
	return (NULL);
}

/**
 * @brief Iterates through the t_objects linked list and adds it to the
 * t_world struct
 *
 * @param w world struct
 * @param o object linked list
 */
void	parse_world(t_world *w, t_objects *o)
{
	t_objects	*p;
	t_objects	*t;
	int			count;

	if (!w)
		return ;
	w->bvh_obj = NULL;
	w->bvh = NULL;
	if (!o)
		return ;
	p = o;
	while (p)
	{
		t = parse_create_object(p);
		if (t)
			world_add_back(w, t, p->type);
		p = p->next;
	}
	parse_free_objects(o);
	w->bvh_obj = obj2arr(w->objs);
	count = obj_sphere_count(w->objs);
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
		p = p->next;
	}
	c.object = c.ambient + c.light + c.cylinder + c.sphere;
	return (c);
}

int	parse_check_object_count(t_objects *o)
{
	t_parse	p;
	int		total;

	p = parse_object_count(o);
	total = p.ambient + p.camera + p.cylinder + p.light + p.plane + p.sphere;
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
	char		*file_content;
	char		**temp;
	t_objects	*o;

	if (check_rt_file(file) == FALSE)
		return (NULL);
	file_content = read_rt_file(file);
	if (file_content == NULL)
		return (NULL);
	temp = ft_split(file_content, '\n');
	o = parse_object(temp);
	if (o == NULL)
		return (free(file_content), free_str_arr(temp), NULL);
	if (!parse_check_object_count(o))
		return (free(file_content), free_str_arr(temp),
			parse_free_objects(o), NULL);
	free_str_arr(temp);
	free(file_content);
	return (o);
}
