/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/10 12:07:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/vec3.h"
#include "../includes/camera.h"
#include "../includes/objects.h"
#include "../includes/render.h"
#include "../includes/mlx_dat.h"
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

t_world	*world_init(t_world *world)
{
	t_objects	*tmp;

	tmp = malloc(sizeof(t_objects));
	if (!tmp)
		return (NULL);
	world->objs = tmp;
	world->objs->type = OBJ_SPHERE;
	world->objs->sphere = sphere(create_vec3(0.5, 0, -1.0), 0.45);
	tmp = malloc(sizeof(t_objects));
	if (!tmp)
		return (NULL);
	world->objs->next = tmp;
	world->objs->next->type = OBJ_SPHERE;
	world->objs->next->sphere = sphere(create_vec3(-0.5, 0.0, -1.0), 0.45);
	world->objs->next->next = NULL;
	return (world);
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
	t_world	world;

	(void)argc;
	(void)argv;
	// TODO: .rt parser
	rt_dat_init(&rt_dat);
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (0); // TODO: malloc failure msg
	if (!world_init(&world))
		return (0); // TODO: malloc failure msg
	cam_init(&cam, &rt_dat);
	render(&rt_dat, &cam, &world);
	// TODO: renderer
	mlx_loop(rt_dat.mlx_dat->mlx);
	rt_dat_free(&rt_dat);
	world_free(&world);
	return (0);
}
