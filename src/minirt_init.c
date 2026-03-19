/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:37:57 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/19 16:25:21 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mrt	*init_mrt(void)
{
	t_mrt	*res;

	res = malloc(sizeof(t_mrt));
	if (!res)
		return (NULL);
	res->image_width = WIDTH;
	res->image_height = WIDTH / ASPECT_RATIO;
	res->viewport_height = 2;
	res->viewport_width = res->viewport_height
					* ((double)(res->image_width / res->image_height));
	res->mlx = init_mlx(res->image_height);
	if (!res->mlx)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

void	free_mrt(t_mrt *m)
{
	mlx_free_all(m->mlx);
	free(m);
}
