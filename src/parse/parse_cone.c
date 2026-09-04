/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 17:00:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 18:15:09 by wshou-xi         ###   ########.fr       */
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
	t_cone		cone;
	char		**res;
	t_objects	*o;

	if (!check_cone(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (free_str_arr(res), FALSE);
	cone.pos = parse_cords(res[1]);
	cone.axis = unit_vec(parse_cords(res[2]));
	cone.radius = ft_atof(res[3]);
	cone.height = ft_atof(res[4]);
	cone.color = parse_color(res[5]);
	cone.material = create_lambertian(cone.color);
	cone.constant_k = 1.0 + pow(cone.radius / cone.height, 2);
	if (!cone.material)
		return (free_str_arr(res), FALSE);
	o = create_object(&cone, OBJ_CONE, id);
	return (obj_add_back(o, obj), free_str_arr(res), TRUE);
}
