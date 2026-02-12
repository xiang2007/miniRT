/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:23:30 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 16:23:32 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t size)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (i < size)
	{
		s[i] = 0;
		i++;
	}
}
