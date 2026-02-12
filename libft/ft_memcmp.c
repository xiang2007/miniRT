/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:28:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 16:28:04 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t				i;
	const unsigned char	*s;
	const unsigned char	*d;

	i = 0;
	s = (const unsigned char *)s1;
	d = (const unsigned char *)s2;
	while (i < size)
	{
		if (s[i] != d[i])
			return (s[i] - d[i]);
		i++;
	}
	return (0);
}
