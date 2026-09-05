/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_object2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:23:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 01:51:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "threadpool.h"
#include "../../includes/parse.h"

int	parse_arg_count(char **arg)
{
	int	size;

	size = 0;
	if (!arg || !*arg)
		return (-1);
	while (arg[size])
	{
		if (!arg[size][0])
			return (-1);
		size++;
	}
	return (size);
}

t_objects	*parse_cylinder_helper(int id, char **res)
{
	t_objects	*o;

	o = malloc(sizeof(t_objects));
	if (!o)
		return (NULL);
	o->id = id;
	o->type = OBJ_CYLINDER;
	o->cylinder.center = parse_cords(res[1]);
	o->cylinder.axis = parse_cords(res[2]);
	if (vec3_len_sq(o->cylinder.axis) > 0.0)
		o->cylinder.axis = unit_vec3(o->cylinder.axis);
	o->cylinder.radius = ft_atof(res[3]) / 2.0;
	o->cylinder.height = ft_atof(res[4]);
	o->cylinder.color = parse_color(res[5]);
	if (o->cylinder.color.r == -1)
		return (free(o), NULL);
	o->cylinder.material = NULL;
	if (res[6])
	{
		if (!parse_material(res, &o, 6))
			return (free(o), NULL);
	}
	else
		o->cylinder.material = create_lambertian(o->cylinder.color);
	o->hit = &cylinder_hit;
	o->translate = &cylinder_translate;
	o->rotate = &cylinder_rotate;
	return (o);
}

int	parse_cylinder(int id, char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!check_cylinder(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = parse_cylinder_helper(id, res);
	if (!o)
	{
		return (free(o), free_str_arr(res), FALSE);
	}
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}

void	print_objects(t_objects *o)
{
	const char	*objs[] = {"Ambient", "Camera", "Sphere", "Plane",
		"Cylinder", "Light", "Cam_setup", "Cone"};
	t_objects	*p;

	if (!o)
		return ;
	p = o;
	while (p)
	{
		printf("%s\n", objs[p->type]);
		p = p->next;
	}
}

void	print_object(t_objects *o)
{
	const char	*objs[] = {"Ambient", "Camera", "Sphere", "Plane",
		"Cylinder", "Light", "Cam_setup", "Cone"};
	t_objects	*p;

	if (!o)
		return ;
	p = o;
	printf("%s\n", objs[p->type]);
}
