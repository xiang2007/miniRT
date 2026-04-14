/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:23:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 14:19:26 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	check_ambient_lightning(char *s)
{
	int		i;
	double	temp;
	char	**t1;
	char	**t2;

	t1 = ft_split(s, ' ');
	if (!check_float(t1[1]))
		return (FALSE);
	temp = ft_atof(t1[1]);
	if (temp < 0 || temp > 1)
		return (free_str_arr(t1), FALSE);
	if (!check_color(t1[2]))
		return (free_str_arr(t1), FALSE);
	t2 = ft_split(t1[2], ',');
	i = 0;
	while(t2[i])
	{
		temp = ft_atoi(t2[i]);
		if (temp < 0 || temp > 255)
			return (free_str_arr(t1), free_str_arr(t2), FALSE);
		i++;
	}
	return (free_str_arr(t1), free_str_arr(t2), TRUE);
}

int	check_cam(char *s)
{
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	i = 1;
	res = ft_split(s, ' ');
	while(res[i])
	{
		if (check_cords(res[0][i]) == FALSE)
			return (free_str_arr(res), FALSE);
		i++;
	}
	if (check_norm_vector(res[1]) == FALSE)
		return (free_str_arr(res), FALSE);
	i = ft_atoi(res[2]);
	if (i < 0 || i > 180)
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

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
	return (size + 1);
}

int	parse_cylinder(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!s || !obj)
		return (FALSE);
	if (!ft_strncmp(s, "cy", 2) || s[2] != 32)
		return (FALSE);
	res = ft_split(s, ' ');
	if (parse_arg_count(res) != 6)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]) || !check_norm_vector(res[2])
			|| !check_float(res[3]) || !check_float(res[4])
			|| !check_color(res[5]))
		return (free_str_arr(res), FALSE);
	o = malloc(sizeof(t_objects));
	o->type = OBJ_CYLINDER;
	o->cylinder.center = parse_cords(res[1]);
	o->cylinder.axis = parse_cords(res[2]);
	o->cylinder.radius = ft_atof(res[3]);
	o->cylinder.height = ft_atof(res[4]);
	o->cylinder.color = parse_color(res[5]);
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}
