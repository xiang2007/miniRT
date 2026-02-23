/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:54:45 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/23 12:58:27 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	*matrix_to_point(t_matrix *m)
{
	t_tuple	*t;

	if (!m)
		return (NULL);
	t = create_point(m->matrix[0][0], m->matrix[1][0], m->matrix[2][0]);
	if (!t)
		return (NULL);
	return (t);
}

t_tuple	*matrix_to_vector(t_matrix *m)
{
	t_tuple	*t;

	if (!m)
		return (NULL);
	t = create_vector(m->matrix[0][0], m->matrix[1][0], m->matrix[2][0]);
	if (!t)
		return (NULL);
	return (t);
}
