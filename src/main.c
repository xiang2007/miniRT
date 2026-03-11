/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/11 16:39:09 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_to_hex(int r, int g, int b)
{
	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

int	main()
{
	t_mlx	*mlx;
	int		color;
	int		x;
	int		y;
	double	r;
	double	g;
	double	b;

	mlx = malloc(sizeof(t_mlx));
	init_mlx(mlx);
	x = 0;
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			r = (double)x / (WIDTH - 1);
			g = (double)y / (HEIGHT - 1);
			b = 0;
			color = rgb_to_hex(
						((int)(r * 255.999)),
						((int)(g * 255.999)),
						((int)(b * 255.999)));
			mlx_put_pixel(mlx, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_to_window(mlx);
	mlx_loop(mlx->mlx);
	close_all(mlx);
}
