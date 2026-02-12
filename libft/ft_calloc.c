/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:23:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2025/06/04 20:25:07 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*dst;

	if (!nitems || size <= 0)
		return (malloc(0));
	if (nitems > SIZE_MAX / size)
		return (NULL);
	dst = malloc(nitems * size);
	if (!dst)
		return (NULL);
	ft_bzero(dst, (nitems * size));
	return (dst);
}
