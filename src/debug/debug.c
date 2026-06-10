/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:02:05 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/02 22:02:05 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	print_vec3(t_vec3 v)
{
	printf("x: %f y: %f z: %f\n", v.x, v.y, v.z);
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