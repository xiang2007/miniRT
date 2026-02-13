/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:09:00 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 17:34:38 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*create_color(t_d red, t_d green, t_d blue)
{
	t_color	*c;

	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	c->red = red;
	c->green = green;
	c->blue = blue;
	return (c);
}

t_color	*add_color(t_color *c1, t_color *c2)
{
	t_color	*c;

	if (!c1 || !c2)
		return (NULL);
	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	c->red = c1->red + c2->red;
	c->green = c1->green + c2->green;
	c->blue = c1->blue + c2->blue;
	return (c);
}

t_color	*sub_color(t_color *c1, t_color *c2)
{
	t_color	*c;

	if (!c1 || !c2)
		return (NULL);
	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	c->red = c1->red - c2->red;
	c->green = c1->green - c2->green;
	c->blue = c1->blue - c2->blue;
	return (c);
}

t_color	*mult_color(t_color *c1, t_color *c2)
{
	t_color	*c;

	if (!c1 || !c2)
		return (NULL);
	c = malloc(sizeof(t_color));
	if (!c)
		return (NULL);
	c->red = c1->red * c2->red;
	c->green = c1->green * c2->green;
	c->blue = c1->blue * c2->blue;
	return (c);
}