/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:45:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 23:03:55 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	obj_add_back(t_objects *src, t_objects **dest)
{
	t_objects	*ptr;

	if (!dest)
		return ;
	if (!src)
		return ;
	if (!*dest)
	{
		*dest = src;
		src->next = NULL;
		return ;
	}
	ptr = *dest;
	while(ptr->next)
		ptr = ptr->next;
	ptr->next = src;
	src->next = NULL;
}

