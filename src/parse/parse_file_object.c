/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:04:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/16 11:41:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/material.h"
#include "../../includes/color.h"

int	parse_ambient(int id, char *s, t_objects **obj)
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
	o->id = id;
	o->type = OBJ_AMBIENT;
	o->ambient.ratio = ratio;
	o->ambient.color = parse_color(res[2]);
	if (o->ambient.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	obj_add_back(o, obj);
	return (free_str_arr(res), TRUE);
}

int	parse_cam(int id, char *s, t_objects **obj)
{
	double		temp;
	char		**res;
	t_objects	*o;

	if (s[0] == 'C' && s[1] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	if (!check_norm_vector(res[2]))
		return (free_str_arr(res), FALSE);
	temp = ft_atof(res[3]);
	if (temp < 0 || temp > 180)
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (free_str_arr(res), FALSE);
	o->id = id;
	o->cam_setup.center = parse_cords(res[1]);
	o->cam_setup.norm_vector = parse_cords(res[2]);
	o->cam_setup.fov = temp;
	o->type = OBJ_SETUP_CAM;
	return (obj_add_back(o, obj), free_str_arr(res), TRUE);
}

int	parse_light(int id, char *s, t_objects **obj)
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
	o->id = id;
	o->light.cords = parse_cords(res[1]);
	o->light.brightness_ratio = ft_atof(res[2]);
	o->type = OBJ_LIGHT;
	obj_add_back(o, obj);
	free_str_arr(res);
	return (TRUE);
}

int	parse_sphere(int id, char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;
	double		ri;

	if (!check_sphere(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	o->id = id;
	o->sphere.point = parse_cords(res[1]);
	o->sphere.radius = ft_atof(res[2]);
	o->sphere.color = parse_color(res[3]);
	if (o->sphere.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	o->sphere.material = NULL;
	if (res[4])
	{
		if (ft_strcmp(res[4], "lambertian") == TRUE)
			o->sphere.material = create_lambertian(o->sphere.color);
		else if (ft_strcmp(res[4], "metal") == TRUE)
			o->sphere.material = create_metal(o->sphere.color, 0.3);
		else if (ft_strcmp(res[4], "dielectric") == TRUE)
		{
			ri = ft_atof(res[5]);
			o->sphere.material = create_dielectric(ri);
		}
		if (!o->sphere.material)
			return (free(o), free_str_arr(res), FALSE);
	}
	else
		o->sphere.material = create_lambertian(o->sphere.color);
	o->type = OBJ_SPHERE;
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}

int	parse_plane(int id, char *s, t_objects **obj)
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
	o->id = id;
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
