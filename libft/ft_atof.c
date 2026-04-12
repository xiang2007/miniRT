/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:25:24 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/12 16:11:10 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atof_helper(char *s, int t)
{
	int		i;
	int		j;
	int		d;
	double	temp;
	double	res;

	i = t;
	d = 1;
	while(s[i])
	{
		if (!ft_isdigit(s[i]))
			return (INT32_MAX);
		j = 0;
		temp = ft_atoi(s[i]);
		while(j < d)
		{
			temp /= 10;
			j++;
		}
		d++;
		res += temp;
		i++;
	}
	return (temp);
}

double	ft_atof(char *str)
{
	double	res;
	int		neg;
	int		i;

	if (!str)
		return (0);
	i = 0;
	neg = 1;
	if (str[0] == '-')
		neg = -1;
	while(str[i])
	{
		while (str[i] != '.')
		{
			if (!ft_isdigit(str[i]))
				return (0);
			res += (double)ft_atoi(str[i]);
			i++;
		}
		i++;
		res += ft_atof_helper(str, i);
	}
	return (res);
}
