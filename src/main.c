/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/12 17:08:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdbool.h>

int	hit_sphere(t_vec3 center, double radius, t_ray r);

int	rgb_to_hex(int r, int g, int b)
{
	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

int	ray_color(t_ray r)
{
	t_vec3	unit_dir;
	t_vec3	n;
	t_color	res;
	double	t;
	double	a;

	t = hit_sphere(create_vec3(0, 0, -1), 0.5, r);
	if (t > 0)
	{
		n = unit_vec(sub_vec(ray_pos(r, t), create_vec3(0, 0, -1)));
		return (0.5 * (rgb_to_hex(n.x + 1, n.y + 1, n.z + 1)));
	}
	unit_dir = unit_vec(r.vec);
	a = 0.5 * (unit_dir.y + 1);
	res = add_color((mult_color_n(create_color(1, 1, 1), (1 - a))),
				(mult_color_n(create_color(0.5, 0.7, 1), a)));
	return (res.color);
}

int	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	ori_center;
	double	a;
	double	b;
	double	c;
	double	d;

	ori_center = sub_vec(center, r.point);
	a = dot_vec(r.vec, r.vec);
	b = -2 * dot_vec(r.vec, ori_center);
	c = dot_vec(ori_center, ori_center) - (radius * radius);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	else
		return (-b - sqrt(d)) / (2 * a);
}

int	main()
{
	t_mlx	*mlx = malloc(sizeof(t_mlx));
	// Image
	int	image_height = (WIDTH / ASPECT_RATIO);
	init_mlx(mlx, image_height);

	// Camera
	double	focal_len = 1;
	double	viewport_height = 2;
	double	viewport_width = viewport_height * ((double)WIDTH / image_height);
	t_vec3	cam_center = {0, 0, 0};

	// calculate the vector across the horizontaland down the vertical viewport edges
	t_vec3	viewport_u = {viewport_width, 0, 0};
	t_vec3	viewport_v = {0, -viewport_height, 0};
	
	// calculate delta u, delta v
	t_vec3	delta_u = div_vec(viewport_u, WIDTH);
	t_vec3	delta_v = div_vec(viewport_v, image_height);

	// calculate the lcoation of the upper left pixel
	t_vec3	viewport_upper_left = sub_vec(sub_vec(sub_vec(cam_center,
			create_vec3(0, 0, focal_len)), (div_vec(viewport_u, 2))),
				div_vec(viewport_v, 2));
	t_vec3	pixel00_loc = add_vec((scale_vec((add_vec(delta_u, delta_v)), 0.5)),
							viewport_upper_left);
	
	int	i = 0;
	while (i < WIDTH)
	{
		int	j = 0;
		while (j < image_height)
		{
			t_vec3	pixel_center = add_vec((add_vec(scale_vec(delta_u, i),
									scale_vec(delta_v, j))), pixel00_loc);
			t_vec3	ray_dir = sub_vec(pixel_center, cam_center);
			t_ray	ray = {cam_center, ray_dir};
			int	color = ray_color(ray);
			mlx_put_pixel(mlx, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_to_window(mlx);
	mlx_loop(mlx->mlx);
	close_all(mlx);
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
