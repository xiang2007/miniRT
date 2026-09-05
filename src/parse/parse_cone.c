/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 17:00:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/31 17:00:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "../../includes/parse.h"

int	check_cone(char *s)
{
	char	**res;

	if (!s)
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res || parse_arg_count(res) != 6)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]) || !check_norm_vector(res[2]))
		return (free_str_arr(res), FALSE);
	if (ft_atof(res[3]) <= 0 || ft_atof(res[4]) <= 0)
		return (free_str_arr(res), FALSE);
	if (!check_color(res[5]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

int	parse_cone(int id, char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!check_cone(s))
		return (FALSE);
	res = ft_split(s, ' ');
	o = malloc(sizeof(t_objects));
	if (!res || !o)
		return (free(o), free_str_arr(res), FALSE);
	o->id = id;
	o->type = OBJ_CONE;
	o->cone.pos = parse_cords(res[1]);
	o->cone.axis = unit_vec3(parse_cords(res[2]));
	o->cone.radius = ft_atof(res[3]);
	o->cone.height = ft_atof(res[4]);
	o->cone.color = parse_color(res[5]);
	o->cone.material = create_lambertian(o->cone.color);
	o->cone.constant_k = 1.0 + pow(o->cone.radius / o->cone.height, 2);
	if (!o->cone.material)
		return (free(o), free_str_arr(res), FALSE);
	o->hit = &cone_hit;
	o->translate = &cone_translate;
	o->rotate = &cone_rotate;
	return (obj_add_back(o, obj), free_str_arr(res), TRUE);
}
