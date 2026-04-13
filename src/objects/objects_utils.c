/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:45:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/13 10:02:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	objects_add_back(t_objects *src, t_objects **dest)
{
	t_objects	*ori;

	ori = *dest;
	while(ori)
		ori = ori->next;
}