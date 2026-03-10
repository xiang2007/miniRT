/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:08:25 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 11:22:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*create_sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->point = create_point(0, 0, 0);
	s->size = 1;
	return (s);
}

void	free_sphere(t_sphere *s)
{
	if (!s)
		return ;
	free(s->point);
	free(s);
}
