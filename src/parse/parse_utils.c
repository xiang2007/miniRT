/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 16:29:58 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 11:43:32 by wshou-xi         ###   ########.fr       */
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
		if (!ft_isdigit(s[i]) || s[0] == '.')
			return (FALSE);
		i++;
	}
	if (s[i] == '.')
		i++;
	if (s[0] == '.' || (s[i - 1] == '.' && s[i] == '\0'))
		return (FALSE);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_color	parse_color(char *s)
{
	char	**arr;
	int		size;
	t_color	res;

	res = (t_color){.r = -1, .g = -1, .b = -1};
	arr = ft_split(s, ',');
	size = 0;
	while (arr[size])
		size++;
	if ((size + 1) != 3)
		return (free_str_arr(arr), res);
	if (!(check_color(s)))
		return (free_str_arr(arr), res);
	res = (t_color){.r = ft_atof(arr[1]), .g = ft_atof(arr[2]),
			.b = ft_atof(arr[3])};
	if ((res.r < 0 || res.r > 255) || (res.g < 0 || res.g > 255)
		|| (res.b < 0 || res.b > 255))
		return (free_str_arr(arr), ((t_color){.r = -1, .g = -1, .b = -1}));
	return (free_str_arr(arr), res);
}

t_point3	parse_cords(char *s)
{
	char		**res;
	t_point3	point;

	point = (t_point3){.x = -1, .y = -1, .z = -1};
	if (!s)
		return (point);
	if (!check_cords(s))
		return (point);
	res = ft_split(s, ',');
	point = (t_point3){.x = ft_atof(res[0]),
				.y = ft_atof(res[1]), .z = ft_atof(res[2])};
	free_str_arr(res);
	return (point);
}
