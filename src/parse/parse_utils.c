/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:29:58 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/12 13:54:48 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	print_str_arr(char **str_arr)
{
	int	i;

	if (!str_arr || !*str_arr)
		return ;
	i = 0;
	while (str_arr[i])
	{
		printf("[\"%s\"] ", str_arr[i]);
		i++;
	}
	printf("\n");
	return ;
}

void	free_str_arr(char **strarr)
{
	int	i;

	if (!strarr)
		return ;
	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
	return ;
}

int	check_float(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (FALSE);
	if (s[i] == '-')
		i++;
	while (s[i] && s[i] != '.')
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	if (s[i] == '.')
		i++;
	while(s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
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
		while(color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	if (i != 2)
		return (FALSE);
	return (TRUE);
}

t_color	parse_color(char *s)
{
	char	**arr;
	int		size;
	t_color	res;

	res = (t_color){-1, -1, -1};
	arr = ft_split(s, ",");
	while (arr[size])
		size++;
	if ((size + 1) != 3)
		return (free_str_arr(arr), res);
	if (!(check_color(s)))
		return (free_str_arr(arr), res);
	res = (t_color){ft_atof(arr[1]), ft_atof(arr[2]), ft_atof(arr[3])};
	if ((res.r < 0 || res.r > 255) || (res.g < 0 || res.g > 255)
		|| (res.b < 0 || res.b > 255))
		return (free_str_arr(arr), (t_color){-1, -1, -1});
	return (free_str_arr(arr), res);
}
