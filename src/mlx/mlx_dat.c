/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_dat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:38:20 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/02 20:20:23 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx	*mlx_dat_init(t_mlx **mlx_dat)
{
	t_mlx	*m;

	m = malloc(sizeof(t_mlx));
	if (!m)
		return (NULL);
	m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, WIDTH / ASPECT_RATIO, "miniRT");
	m->img = mlx_new_image(m->mlx, WIDTH, WIDTH / ASPECT_RATIO);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);
	*mlx_dat = m;
	return (m);
}

void	mlx_dat_free(t_mlx *mlx_dat)
{
	mlx_destroy_image(mlx_dat->mlx, mlx_dat->img);
	mlx_destroy_window(mlx_dat->mlx, mlx_dat->mlx_win);
	mlx_destroy_display(mlx_dat->mlx);
	free(mlx_dat->mlx);
	free(mlx_dat);
}
