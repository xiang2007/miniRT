/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:25:24 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/13 09:26:10 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	int		dot;
	int		neg;
	double	res1;
	char	*s1;
	char	*s2;

	dot = 0;
	while (str[dot] && str[dot] != '.')
		dot++;
	if (dot == (int)ft_strlen(str))
		return (ft_atoi(str));
	neg = 1;
	if (str[0] == '-')
	{
		s1 = ft_substr(str, 1, dot - 1);
		neg = -1;
	}
	else
		s1 = ft_substr(str, 0, dot);
	s2 = ft_substr(str, dot + 1, (ft_strlen(str) - dot));
	res1 = ft_atoi(s2);
	while (ft_strlen(str) - (++dot))
		res1 /= 10;
	res1 += (double)ft_atoi(s1);
	return (free(s1), free(s2), (res1 * neg));
}
