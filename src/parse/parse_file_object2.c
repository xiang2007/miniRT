/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_object2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:36:40 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 12:40:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "material.h"
#include "objects.h"
#include "../../includes/parse.h"
#include "vec3.h"

t_objects	*parse_plane_helper(int id, char **res)
{
	t_objects	*o;

	o = malloc(sizeof(t_objects));
	if (!o)
		return (NULL);
	o->id = id;
	o->type = OBJ_PLANE;
	o->plane.center = parse_cords(res[1]);
	o->plane.axis = parse_cords(res[2]);
	if (vec3_len_sq(o->plane.axis) > 0.0)
		o->plane.axis = unit_vec3(o->plane.axis);
	o->plane.color = parse_color(res[3]);
	if (o->plane.color.r == -1)
		return (free(o), NULL);
	o->plane.material = parse_optional_material(res, 4, o->plane.color);
	if (res[4] && !o->plane.material)
		return (free(o), NULL);
	o->hit = &plane_hit;
	o->translate = &plane_translate;
	o->rotate = &plane_rotate;
	return (o);
}

t_color	parse_color_swtitch(t_objects **o)
{
	t_color	cl;

	cl = (t_color){0};
	if ((*o)->type == OBJ_CYLINDER)
		cl = (*o)->cylinder.color;
	else if ((*o)->type == OBJ_SPHERE)
		cl = (*o)->sphere.color;
	else if ((*o)->type == OBJ_PLANE)
		cl = (*o)->plane.color;
	return (cl);
}

t_material	*parse_mat_switch(char **res, int idx, t_color cl, double ri)
{
	t_material	*mat;

	mat = NULL;
	if (ft_strcmp(res[idx], "lambertian") == TRUE)
		mat = create_lambertian(cl);
	else if (ft_strcmp(res[idx], "metal") == TRUE)
	{
		if (res[idx + 1])
			ri = ft_atof(res[idx + 1]);
		else
			ri = 0.3;
		mat = create_metal(cl, ri);
	}
	else if (ft_strcmp(res[idx], "dielectric") == TRUE)
	{
		if (res[idx + 1])
			ri = ft_atof(res[idx + 1]);
		else
			ri = 1.50;
		mat = create_dielectric(ri);
	}
	return (mat);
}

bool	parse_material(char **res, t_objects **o, int idx)
{
	t_color		cl;
	t_material	*mat;

	mat = NULL;
	cl = parse_color_swtitch(o);
	mat = parse_mat_switch(res, idx, cl, 0);
	if (!mat)
		return (free((*o)), free_str_arr(res), FALSE);
	if ((*o)->type == OBJ_CYLINDER)
		(*o)->cylinder.material = mat;
	else if ((*o)->type == OBJ_SPHERE)
		(*o)->sphere.material = mat;
	else if ((*o)->type == OBJ_PLANE)
		(*o)->plane.material = mat;
	return (TRUE);
}
