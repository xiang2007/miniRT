/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 23:45:47 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/12 23:45:47 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*create_tuple(t_d x, t_d y, t_d z, int w)
{
	t_tuple	*tuple;

	tuple = malloc(sizeof(t_tuple));
	if (!tuple)
		return (NULL);
	tuple->x = x;
	tuple->y = y;
	tuple->z = x;

}