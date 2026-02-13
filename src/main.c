/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:50:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 18:49:30 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	main(void)
{
	t_mlx	m;

	m.mlx = mlx_init();
	m.mlx_win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "Fractol");
	m.img = mlx_new_image(m.mlx, WIDTH, HEIGHT);
	m.addr = mlx_get_data_addr(m.img, &m.bpp,
			&m.line_length, &m.endian);
	for(int i = 0; i < 100; i++)
		for (int j = i + 1; i < 200; i++)
			mlx_put_pixel(&m, i, j, 0xFF0000);
	mlx_put_image_to_window(m.mlx, m.mlx_win, m.img, 0, 0);
	mlx_hook(m.mlx_win, 17, 1L << 17, close_all, &m);
	mlx_loop(m.mlx);
	return 0;
}
