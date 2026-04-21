/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/21 12:28:21 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/vec3.h"
#include "../includes/camera.h"
#include "../includes/objects.h"
#include "../includes/render.h"
#include "../includes/mlx_dat.h"
#include "../includes/parse.h"
#include "../libft/libft.h"
#include <../mlx_Linux/mlx.h>
#include <stdlib.h>

void	rt_dat_init(t_rt *rt_dat)
{
	rt_dat->aspect_ratio = (double)16 / 9;
	rt_dat->img_w = WIDTH;
	rt_dat->img_h = WIDTH / rt_dat->aspect_ratio;
	if (rt_dat->img_h < 1)
		rt_dat->img_h = 1;
}

void	rt_dat_free(t_rt *rt_dat)
{
	mlx_dat_free(rt_dat->mlx_dat);
	free(rt_dat);
}

void	multilple_object(t_world *w)
{
	t_sphere	t;
	t_objects	*r;

	t = sphere(create_vec3(0.5, 0, -1.0), 0.45);
	r = create_object(&t, OBJ_SPHERE);
	world_add_back(w, r, OBJ_SPHERE);
	t = sphere(create_vec3(-0.5, 0, -1.0), 0.45);
	r = create_object(&t, OBJ_SPHERE);
	world_add_back(w, r, OBJ_SPHERE);
	t = sphere(create_vec3(0, 0.7, -1.0), 0.5);
	r = create_object(&t, OBJ_SPHERE);
	world_add_back(w, r, OBJ_SPHERE);
	t = sphere(create_vec3(0, -100.5, -1.0), 100);
	r = create_object(&t, OBJ_SPHERE);
	world_add_back(w, r, OBJ_SPHERE);
}

void	world_free(t_world *world)
{
	t_objects	*tmp;

	while (world->objs)
	{
		tmp = world->objs;
		world->objs = world->objs->next;
		free(tmp);
	}
}

int	main(int argc, char **argv)
{
	t_cam	cam;
	t_rt	rt_dat;
	t_world	world = {0};
	t_setup_cam	s;

	(void)argc;
	(void)argv;
	// TODO: .rt parser
	rt_dat_init(&rt_dat);
	s.center = create_vec3(0, 0, 0);
	s.fov = 0;
	s.norm_vector = create_vec3(0, 0, 0);
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (0); // TODO: malloc failure msg
	// if (!world_init())
	// 	return (0); // TODO: malloc failure msg
	multilple_object(&world);
	cam_init(&cam, &rt_dat, &s);
	render(&rt_dat, &cam, &world);
	// TODO: renderer
	mlx_loop(rt_dat.mlx_dat->mlx);
	rt_dat_free(&rt_dat);
	world_free(&world);
	return (0);
}
