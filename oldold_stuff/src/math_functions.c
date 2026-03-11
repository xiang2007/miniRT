/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:15:18 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/04 17:51:21 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_double(double x, double y)
{
	if (fabs(x - y) < EP)
		return (1);
	return (0);
}

double	sq(double n)
{
	return (n * n);
}
