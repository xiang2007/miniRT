/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:52:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 16:06:54 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_intersect_back(t_intersect *src, t_intersect **list)
{
	t_intersect	*pointer;

	if (!src)
		return ;
	if (!list)
	{
		*list = src;
		return ;
	}
	pointer = *list;
	while (pointer->next)
		pointer = pointer->next;
	pointer->next = src;
}
