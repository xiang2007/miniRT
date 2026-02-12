/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:37:27 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/07/14 10:14:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(const char *c);

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = ft_strlen((char *)s);
	while (size >= 0)
	{
		if (s[size] == (char)c)
			return ((char *)&s[size]);
		size--;
	}
	return (NULL);
}
