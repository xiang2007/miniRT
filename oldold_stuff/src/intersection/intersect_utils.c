/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:52:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/10 22:45:41 by wshou-xi         ###   ########.fr       */
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
		printf("List is NULL\n");
		*list = src;
		return ;
	}
	pointer = *list;
	while (pointer->next)
		pointer = pointer->next;
	pointer->next = src;
}

void	free_intersect_list(t_intersect *i)
{
	t_intersect	*next;

	while (i)
	{
		next = i->next;
		free_intersect(i);
		i = next;
	}
}

t_intersect	*hit(t_intersect *i)
{
	t_intersect	*best;
	t_intersect	*head;

	best = NULL;
	head = i;
	while (head)
	{
		if (head->intersects[0] > 0
				&& (!best || head->intersects[0] < best->intersects[0]))
			best = head;
		head = head->next;
	}
	return (best);
}
