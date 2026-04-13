/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:47:03 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/13 15:19:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

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


