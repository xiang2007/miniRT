/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 23:03:14 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/18 10:41:52 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*create_object(void)
{
	t_obj	*res;

	res = malloc(sizeof(t_obj));
	if(!res)
		return (NULL);
	res = (t_obj *){0};
	return (res);
}
