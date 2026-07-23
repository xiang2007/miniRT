/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:47:03 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 00:07:17 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	check_cords(char *s)
{
	int		i;
	char	**cords;

	if (!s)
		return (FALSE);
	cords = ft_split(s, ',');
	i = 0;
	while (cords[i])
	{
		if (!check_float(cords[i]))
			return (free_str_arr(cords), FALSE);
		i++;
	}
	if (i != 3)
		return (free_str_arr(cords), FALSE);
	free_str_arr(cords);
	return (TRUE);
}

int	check_norm_vector(char *s)
{
	int		i;
	double	temp;
	char	**norm;

	if (!s)
		return (FALSE);
	norm = ft_split(s, ',');
	i = 0;
	while (norm[i])
	{
		if (!check_float(norm[i]))
			return (free_str_arr(norm), FALSE);
		temp = ft_atof(norm[i]);
		if (temp < -1 || temp > 1)
			return (free_str_arr(norm), FALSE);
		i++;
	}
	if (i != 3)
		return (free_str_arr(norm), FALSE);
	free_str_arr(norm);
	return (TRUE);
}

int	check_color(char *s)
{
	char	**color;
	int		i;
	int		j;

	if (!s)
		return (FALSE);
	color = ft_split(s, ',');
	i = 0;
	while (color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				return (free_str_arr(color), FALSE);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (free_str_arr(color), FALSE);
	return (free_str_arr(color), TRUE);
}

int	check_cylinder(char *s)
{
	char	**res;
	double	t;

	if (!s)
		return (FALSE);
	if ((ft_strncmp(s, "cy", 2) != 0) || s[2] != ' ')
		return (FALSE);
	res = ft_split(s, ' ');
	if (parse_arg_count(res) != 6)
		return (free_str_arr(res), FALSE);
	if (!check_cords(res[1]))
		return (free_str_arr(res), FALSE);
	if (!check_norm_vector(res[2]))
		return (free_str_arr(res), FALSE);
	t = ft_atof(res[3]);
	if (t < 0)
		return (free_str_arr(res), FALSE);
	t = ft_atof(res[4]);
	if (t < 0)
		return (free_str_arr(res), FALSE);
	if (!check_color(res[5]))
		return (free_str_arr(res), FALSE);
	return (free_str_arr(res), TRUE);
}
