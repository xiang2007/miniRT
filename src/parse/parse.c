/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:37:21 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/12 12:45:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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

	if (!o)
		return ;
	p = o;
	while (p)
	{
		if (p->type == OBJ_SPHERE)
		{
			t = create_object(&p->sphere, OBJ_SPHERE, p->id);
			world_add_back(w, t, OBJ_SPHERE);
		}
		if (p->type == OBJ_PLANE)
		{
			t = create_object(&p->plane, OBJ_PLANE, p->id);
			world_add_back(w, t, OBJ_PLANE);
		}
		p = p->next;
	}
	parse_free_objects(o);
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
