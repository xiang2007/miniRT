/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/21 17:37:39 by wshou-xi         ###   ########.fr       */
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
#include <X11/keysym.h>

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

void	parse_world(t_world *w, t_objects *o)
{
	t_objects	*p;
	t_objects	*t;

	if (!o)
		return ;
	p = o;
	while(p)
	{
		if (p->type == OBJ_SPHERE)
		{
			t = create_object(&p->sphere, OBJ_SPHERE);
			world_add_back(w, t, OBJ_SPHERE);
			printf("World added\n");
		}
		p = p->next;
	}
	parse_free_objects(o);
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

int	handle_key(int key, t_rt *win)
{
	if (key == XK_Escape)
	{
		world_free(&win->world);
		mlx_dat_free(win->mlx_dat);
		exit(0);
	}
	return (0);
}

int	close_all(t_rt *win)
{
	world_free(&win->world);
	mlx_dat_free(win->mlx_dat);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cam		cam;
	t_rt		rt_dat;
	t_objects	*objs;
	t_world		world = {0};
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
	objs = parse("test.rt");
	if (!objs)
		return (1);
	parse_world(&world, objs);
	rt_dat.world = world;
	cam_init(&cam, &rt_dat, &s);
	render(&rt_dat, &cam, &world);
	// TODO: renderer
	mlx_hook(rt_dat.mlx_dat->mlx_win, 2, 1L << 0, handle_key, &rt_dat);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 17, 1L << 17, close_all, &rt_dat);
	mlx_loop(rt_dat.mlx_dat->mlx);
	return (0);
}
