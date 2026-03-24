/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 14:34:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdbool.h>

// int	hit_sphere(t_vec3 center, double radius, t_ray r);

int	rgb_to_hex(int r, int g, int b)
{
	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

// int	ray_color(t_ray r)
// {
// 	t_vec3	unit_dir;
// 	t_vec3	n;
// 	t_color	res;
// 	double	t;
// 	double	a;

// 	t = hit_sphere(create_vec3(0, 0, -1), 0.5, r);
// 	if (t > 0)
// 	{
// 		n = unit_vec(sub_vec(ray_pos(r, t), create_vec3(0, 0, -1)));
// 		return (0.5 * (rgb_to_hex(n.x + 1, n.y + 1, n.z + 1)));
// 	}
// 	unit_dir = unit_vec(r.vec);
// 	a = 0.5 * (unit_dir.y + 1);
// 	res = add_color((mult_color_n(create_color(1, 1, 1), (1 - a))),
// 				(mult_color_n(create_color(0.5, 0.7, 1), a)));
// 	return (res.color);
// }

// void	draw_sphere(t_mrt *m)
// {
// 	int		x;
// 	int		y;
// 	double	u;
// 	double	v;
// 	t_vec3	t;
// 	t_ray	r;

// 	x = 0;
// 	while (x < m->image_width)
// 	{
// 		y = 0;
// 		while (y < m->image_height)
// 		{
// 			u = (double)x / (m->image_width - 1);
// 			v = (double)(m->image_height -1 -y) / (m->image_height - 1);
// 			r.point = create_vec3(0, 0, 0);
// 		}
// 	}
// }

int	main()
{
	t_mrt	*minirt;
	t_cam	c;

	minirt = init_mrt();
	minirt->cam_center = create_vec3(0, 0, 0);
	c = cam(*minirt);
	render(minirt, c);
	mlx_loop(minirt->mlx->mlx);
	free_mrt(minirt);
	return (0);
}


// int	main()
// {
// 	t_mlx	*mlx;
// 	t_color	c;
// 	int		x;
// 	int		y;
// 	int		image_height;
// 	int		viewport_height;
// 	int		viewport_width;

// 	mlx = malloc(sizeof(t_mlx));
// 	image_height = (int)(WIDTH / (ASPECT_RATIO));
// 	init_mlx(mlx, image_height);
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < image_height)
// 		{
// 			c.r = (double)x / (WIDTH - 1);
// 			c.g = (double)y / (image_height - 1);
// 			c.b = 0;
// 			c.color = rgb_to_hex(
// 						((int)(c.r * 255.999)),
// 						((int)(c.g * 255.999)),
// 						((int)(c.b * 255.999)));
// 			mlx_put_pixel(mlx, x, y, c.color);
// 			y++;
// 		}
// 		x++;
// 	}
// 	mlx_put_to_window(mlx);
// 	mlx_loop(mlx->mlx);
// 	close_all(mlx);
// 	free(mlx);
// }
