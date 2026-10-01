/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:04:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 12:55:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	init_sphere(t_objects *o, int id, char **res)
{
	o->id = id;
	o->type = OBJ_SPHERE;
	o->sphere.point = parse_cords(res[1]);
	o->sphere.radius = ft_atof(res[2]) / 2.0;
	o->sphere.color = parse_color(res[3]);
	if (o->sphere.color.r == -1)
		return (false);
	o->sphere.material = parse_optional_material(res, 4, o->sphere.color);
	if (res[4] && !o->sphere.material)
		return (false);
	o->hit = &sphere_hit;
	o->translate = &sphere_translate;
	o->rotate = NULL;
	return (true);
}

int	parse_sphere(int id, char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!check_sphere(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (free_str_arr(res), FALSE);
	if (!init_sphere(o, id, res))
		return (free(o), free_str_arr(res), FALSE);
	return (free_str_arr(res), obj_add_back(o, obj), TRUE);
}
