/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:04:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 16:13:03 by wshou-xi         ###   ########.fr       */
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
	if (!check_ambient_lightning(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	ratio = ft_atof(res[1]);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (free_str_arr(res), FALSE);
	o->type = OBJ_AMBIENT;
	o->ambient.ratio = ratio;
	o->ambient.color = parse_color(res[2]);
	if (o->ambient.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	obj_add_back(o, obj);
	return (free_str_arr(res), TRUE);
}

// Not complete, need to make it compatible with t_cam struct
int	parse_cam(char *s, t_objects **obj)
{
	char		**res;

	if (s[0] == 'C' && s[1] != 'C')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	(void)obj;
	return (TRUE);
}

int	parse_light(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!s)
		return (FALSE);
	if (!check_light(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
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

	if (!check_sphere(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	o->sphere.point = parse_cords(res[1]);
	o->sphere.radius = ft_atof(res[2]);
	o->sphere.color = parse_color(res[3]);
	if (o->sphere.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	o->type = OBJ_SPHERE;
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}

int	parse_plane(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!check_plane(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	o->type = OBJ_PLANE;
	o->plane.center = parse_cords(res[1]);
	o->plane.normal = parse_cords(res[2]);
	o->plane.color = parse_color(res[3]);
	if (o->plane.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}
