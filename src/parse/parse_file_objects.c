/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_objects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:04:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 14:39:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	parse_ambient(char *s, t_objects **obj)
{
	double		ratio;
	char		**res;
	t_objects	*o;

	if (!s)
		return (FALSE);
	if (!(s[0] == 'A' && s[1] == 32))
		return (FALSE);
	res = ft_split(s, ' ');
	if (parse_arg_count(res) != 3)
		return (free_str_arr(res), FALSE);
	if (!check_float(res[1]) || !check_color(res[2]))
		return (free_str_arr(res), FALSE);
	ratio = ft_atof(res[1]);
	if (ratio < 0 || ratio > 1)
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	o->ambient.ratio = ratio;
	o->ambient.color = parse_color(2);
	obj_add_back(o, obj);
	return (TRUE);
}

// Not complete, need to make it compatible with t_cam struct
int	parse_cam(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (s[0] == 'C' && res[1] != 'C')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	return (TRUE);
}

int	parse_light(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (s[0] != 'L' && s[1] == 32)
		return (FALSE);
	res = ft_split(s, ' ');
	if (!parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]) || !check_float(res[2]))
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	o->light.cords = parse_cords(res[1]);
	o->light.brightness_ratio = ft_atof(res[2]);
	o->type = OBJ_LIGHT;
	obj_add_back(o, obj);
	free_str_arr(res);
	return (TRUE);
}

int	parse_sphere(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!s || !obj)
		return (FALSE);
	if (!ft_strncmp(s, "sp", 2) && s[2] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]) || !check_float(res[2]) || !check_color(res[3]))
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	o->sphere.point = parse_cords(res[1]);
	o->sphere.radius = ft_atof(res[2]);
	o->sphere.color = parse_color(res[3]);
	o->type = OBJ_SPHERE;
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}

int	parse_plane(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!s || !obj)
		return (FALSE);
	if (!ft_strncmp(s, "pl", 2) && s[2] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]) || !check_norm_vector(res[2])
		|| !check_color(res[3]))
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	o->type = OBJ_PLANE;
	o->plane.center = parse_cords(res[1]);
	o->plane.normal = parse_cords(res[2]);
	o->plane.color = parse_color(res[3]);
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}
