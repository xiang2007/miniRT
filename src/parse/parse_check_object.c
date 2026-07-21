/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:28:09 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 00:03:32 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	check_ambient_lightning(char *s)
{
	char	**res;
	double	temp;

	if (!s)
		return (FALSE);
	if (s[0] != 'A' || s[1] != 32)
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res || !*res)
		return (free_str_arr(res), FALSE);
	if (parse_arg_count(res) != 3)
		return (free_str_arr(res), FALSE);
	if (!check_float(res[1]))
		return (free_str_arr(res), FALSE);
	temp = ft_atof(res[1]);
	if (temp < 0 || temp > 1)
		return (free_str_arr(res), FALSE);
	if (!check_color(res[2]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

int	check_cam(char *s)
{
	int		fov;
	char	**res;

	if (!s)
		return (FALSE);
	if (s[0] != 'C' || s[1] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res || !*res)
		return (FALSE);
	if (parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	if (!check_norm_vector(res[2]))
		return (free_str_arr(res), FALSE);
	fov = ft_atoi(res[3]);
	if (fov < 0 || fov > 180)
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

int	check_light(char *s)
{
	char	**res;
	double	dia;

	if (!s)
		return (FALSE);
	if (s[0] != 'L' || s[1] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	if (parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	dia = ft_atof(res[2]);
	if (dia < 0)
		return (free_str_arr(res), FALSE);
	if (!check_color(res[3]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

int	check_plane(char *s)
{
	char	**res;

	if (!s)
		return (FALSE);
	if ((ft_strncmp(s, "pl", 2) != 0) || s[2] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res || !*res)
		return (FALSE);
	if (parse_arg_count(res) != 4)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	if (!check_norm_vector(res[2]))
		return (free_str_arr(res), FALSE);
	if (!check_color(res[3]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}

int	check_sphere(char *s)
{
	char	**res;
	double	t;

	if (!s)
		return (FALSE);
	if ((ft_strncmp(s, "sp", 2) != 0) || s[2] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res || !*res)
		return (FALSE);
	if (parse_arg_count(res) != 4)
		if (parse_arg_count(res) != 5)
			if (parse_arg_count(res) != 6)
				return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	t = ft_atof(res[2]);
	if (t < 0)
		return (free_str_arr(res), FALSE);
	if (!check_color(res[3]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}
