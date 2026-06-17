/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xorshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:32:57 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/06/18 00:32:57 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief A random number generator that utilise the Xorshift PRNG
 *
 * @param state The previous generated number or the starting seed
 * @return the new random number
 */
uint32_t	ft_xorshift32(t_xorshift32 *state)
{
	uint32_t	x;

	x = state->s;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (state->s = x);
}
