/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:27:51 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 16:27:53 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*cptr;

	cptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((char)cptr[i] == (char)c)
			return ((void *)(cptr + i));
		i++;
	}
	return (NULL);
}
