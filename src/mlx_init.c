/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:38:20 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/19 16:25:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mlx	*init_mlx(int image_height)
{
	t_mlx	*m;

	m = malloc(sizeof(t_mlx));
	if (!m)
		return (NULL);
	m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, image_height, "miniRT");
	m->img = mlx_new_image(m->mlx, WIDTH, image_height);
	m->addr = mlx_get_data_addr(m->img, &m->bpp, &m->line_length, &m->endian);
	return (m);
}

void	mlx_put_pixel(t_mlx *m, int x, int y, int color)
{
	char	*dest;

	dest = m->addr + (y * m->line_length + x * (m->bpp / 8));
	*(unsigned int*)dest = color;
}

void	mlx_put_to_window(t_mlx *m)
{
	t_mlx	temp;

	temp = *m;
	mlx_put_image_to_window(temp.mlx, temp.mlx_win, temp.img, 0, 0);
}

void	mlx_free_all(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}

int	close_all(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
