/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:40:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/06 14:36:18 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max;
	size_t	olen;
	char	*dest;

	if (!s)
		return (NULL);
	olen = ft_strlen((char *)s);
	if (start >= olen)
	{
		dest = malloc(1);
		if (dest)
			dest[0] = '\0';
		return (dest);
	}
	max = olen - start;
	if (len > max)
		len = max;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[start], len + 1);
	return (dest);
}
