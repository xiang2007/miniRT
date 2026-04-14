/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:11:16 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 00:34:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

void	parse_free_objects(t_objects *o)
{
	t_objects	*next;

	if (!o)
		return ;
	while (o)
	{
		next = o->next;
		free(o);
		o = next;
	}
}
