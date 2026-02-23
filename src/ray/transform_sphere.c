/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:39:46 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/23 23:28:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sp	*sphere_transform(t_sp *s, t_matrix *m)
{
	t_sp	*sp;

	if (!s)
		return (NULL);
	sp = create_sphere(x, y, z, s->diameter);
	return (sp);
}

