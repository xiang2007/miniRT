/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:47:03 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 14:38:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
