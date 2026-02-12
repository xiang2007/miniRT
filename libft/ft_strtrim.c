/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:39:41 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/06 14:21:13 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	last;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	last = ft_strlen((char *)s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (last > start && ft_strchr(set, s1[last - 1]))
		last--;
	return (ft_substr(s1, start, (last - start)));
}
