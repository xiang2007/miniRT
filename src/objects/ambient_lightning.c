/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:43:25 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 10:46:50 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_al	*create_ambient_lightning(t_d ratio, t_color *color)
{
	t_al	*res;

	res = malloc(sizeof(t_al));
	if (!res)
		return (NULL);
	res->ratio = ratio;
	res->c = color;
	res->next = NULL;
	return (NULL);
}

void	*add_ambient_lightning(t_al *src, t_al *dest)
{
	if (!src || !dest)
		return (NULL);
	dest->next = src;
}