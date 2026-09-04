/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:04:38 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 12:55:20 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "../../includes/parse.h"

int	parse_ambient(int id, char *s, t_objects **obj)
{
	t_ambient	ambient;
	char		**res;
	t_objects	*o;

	if (!s)
		return (FALSE);
	if (!check_ambient_lightning(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	ambient.ratio = ft_atof(res[1]);
	ambient.color = parse_color(res[2]);
	if (ambient.color.r == -1)
		return (free_str_arr(res), FALSE);
	o = create_object(&ambient, OBJ_AMBIENT, id);
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
	t_light		light;
	char		**res;
	t_objects	*o;

	if (!s)
		return (FALSE);
	if (!check_light(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	light.cords = parse_cords(res[1]);
	light.brightness_ratio = ft_atof(res[2]);
	light.color = parse_color(res[3]);
	o = create_object(&light, OBJ_LIGHT, id);
	return (obj_add_back(o, obj), free_str_arr(res), TRUE);
}

int	parse_sphere(int id, char *s, t_objects **obj)
{
	t_sphere	sphere;
	char		**res;
	t_objects	*o;

	if (!check_sphere(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	sphere.point = parse_cords(res[1]);
	sphere.radius = ft_atof(res[2]) / 2.0;
	sphere.color = parse_color(res[3]);
	if (sphere.color.r == -1)
		return (free_str_arr(res), FALSE);
	if (res[4])
	{
		sphere.material = parse_mat_switch(res, 4, sphere.color, 0);
		if (!sphere.material)
			return (free_str_arr(res), FALSE);
	}
	else
		sphere.material = create_lambertian(sphere.color);
	o = create_object(&sphere, OBJ_SPHERE, id);
	return (free_str_arr(res), obj_add_back(o, obj), TRUE);
}

int	parse_plane(int id, char *s, t_objects **obj)
{
	t_plane		plane;
	char		**res;
	t_objects	*o;

	if (!check_plane(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	if (parse_plane_helper(id, res, &plane) == FALSE)
		return (free_str_arr(res), FALSE);
	o = create_object(&plane, OBJ_PLANE, id);
	obj_add_back(o, obj);
	return (free_str_arr(res), TRUE);
}
