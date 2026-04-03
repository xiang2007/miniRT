/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:31:56 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/02 22:31:56 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	mlx_put_pixel(t_mlx *m, int x, int y, int color)
{
	char	*dest;

	dest = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int *)dest = color;
}

void	mlx_put_to_window(t_mlx *m)
{
	t_mlx	temp;

	temp = *m;
	mlx_put_image_to_window(temp.mlx, temp.mlx_win, temp.img, 0, 0);
}
