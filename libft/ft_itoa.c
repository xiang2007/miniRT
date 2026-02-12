/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:25:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/14 18:06:09 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned int n);
static char	*pcha(unsigned int n, int size, int sign);

char	*ft_itoa(unsigned int n)
{
	int	size;
	int	sign;

	sign = 0;
	if (n == 0)
		return (ft_strdup("0"));
	size = ft_count(n);
	return (pcha(n, size, sign));
}

static char	*pcha(unsigned int n, int size, int sign)
{
	char	*dest;
	int		tsize;

	tsize = size + sign;
	dest = (char *)malloc(tsize + 1);
	if (!dest)
		return (NULL);
	dest[tsize] = '\0';
	while (n > 0)
	{
		dest[--tsize] = (n % 10) + '0';
		n /= 10;
	}
	return (dest);
}

static int	ft_count(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}
