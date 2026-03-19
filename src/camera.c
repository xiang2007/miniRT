/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:43 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/19 17:51:31 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_cam(t_cam *cam, t_mrt m)
{
	cam->aspect_ratio = ASPECT_RATIO;
	cam->cam_center = m.cam_center;
	cam->image_width = WIDTH;
	cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
	if (cam->image_height < 1)
		cam->image_height = 1;
	cam->viewport_height = 2;
	cam->viewport_width = cam->viewport_height
					* ((double)(cam->image_width) / cam->image_height);
	cam->viewport_u = create_vec3(cam->viewport_width, 0, 0);
	cam->viewport_v = create_vec3(0, -(cam->viewport_height), 0);
	cam->pixel_delta_u = div_vec(cam->viewport_u, cam->image_width);
	cam->pixel_delta_v = div_vec(cam->viewport_v, cam->image_height);
	cam->viewport_upper_left = sub_vec(sub_vec(sub_vec(cam->cam_center,
									create_vec3(0, 0, 1)),
									div_vec(cam->viewport_u, 2)),
									div_vec(cam->viewport_v, 2));
	cam->pixel00_loc = add_vec(cam->viewport_upper_left,
							scale_vec(add_vec(cam->pixel_delta_u
								,cam->pixel_delta_v), 0.5));
}

void	print_cam(t_cam	c)
{
	printf("image width: %d\nimage_height: %d", c.image_width, c.image_height);
	printf("\nfov: %f\naspect ratio:%f\n", c.fov, c.aspect_ratio);
	printf("viewport_height: %f\nviewport_width: %f\n"
			, c.viewport_height, c.viewport_width);
	printf("Cam center: ");
	print_vec3(c.cam_center);
	printf("viewport_u: ");
	print_vec3(c.viewport_u);
	printf("viewport_v: ");
	print_vec3(c.pixel_delta_v);
	printf("pixel_delta_u: ");
	print_vec3(c.pixel_delta_u);
	printf("pixel_delta_v: ");
	print_vec3(c.pixel_delta_v);
	printf("viewport_upper_left: ");
	print_vec3(c.viewport_upper_left);
	printf("pixel at 0,0 location: ");
	print_vec3(c.pixel00_loc);
}

void	render(t_mrt *m, t_cam c)
{
	int		i;
	int		j;
	t_ray	r;
	t_color	cl;
	t_vec3	p_center;
	t_vec3	r_dir;

	j = 0;
	while (j < m->image_height)
	{
		i = 0;
		while (i < m->image_width)
		{
			p_center = add_vec(c.pixel00_loc,
						add_vec(scale_vec(c.pixel_delta_u, i),
						scale_vec(c.pixel_delta_v, j)));
			r_dir = sub_vec(p_center, c.cam_center);
			r = ray(c.cam_center, r_dir);
			cl = ray_color(r);
			mlx_put_pixel(m->mlx, i, j, cl.color);
			i++;
		}
		j++;
	}
	mlx_put_to_window(m->mlx);
}

// if mrt strcut is not set, im cooked
t_cam	cam(t_mrt mrt)
{
	t_cam	cam;

	cam = (t_cam){0};
	init_cam(&cam, mrt);
	return (cam);
}
