/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:23:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/13 23:39:20 by wshou-xi         ###   ########.fr       */
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
