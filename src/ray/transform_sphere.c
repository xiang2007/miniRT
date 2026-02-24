/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:39:46 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/24 15:21:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sp	*transform_sphere(t_sp *s, t_matrix *m)
{
	t_sp	*res;
	t_tuple	*t;

	if (!s || !m)
		return (NULL);
	t = matrix_to_point(m);
	res = create_sphere(t, s->diameter);
	if (!res)
		return (free(t), NULL);
	free(t);
	return (res);
}
