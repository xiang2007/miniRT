/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/05/12 00:15:26 by wshou-xi         ###   ########.fr       */
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

/**
 * @brief Setup ray tracer config data like aspect ratio, image height & width
 *
 * @param rt_dat pointer to the data struct
 */
void	rt_dat_init(t_rt *rt_dat)
{
	rt_dat->aspect_ratio = (double)16 / 9;
	rt_dat->img_w = WIDTH;
	rt_dat->img_h = WIDTH / rt_dat->aspect_ratio;
	if (rt_dat->img_h < 1)
		rt_dat->img_h = 1;
	rt_dat->init = 0;
}

/**
 * @brief Frees the ray tracer data struct
 *
 * @param rt_dat pointer to the data struct
 */
void	rt_dat_free(t_rt *rt_dat)
{
	mlx_dat_free(rt_dat->mlx_dat);
	free(rt_dat);
}

/**
 * @brief Iterates through the t_objects linked list and adds it to the
 * t_world struct
 *
 * @param w world struct
 * @param o object linked list
 */
void	parse_world(t_world *w, t_objects *o)
{
	t_objects	*p;
	t_objects	*t;

	if (!o)
		return ;
	p = o;
	while (p)
	{
		if (p->type == OBJ_SPHERE)
		{
			t = create_object(&p->sphere, OBJ_SPHERE);
			world_add_back(w, t, OBJ_SPHERE);
		}
		if (p->type == OBJ_PLANE)
		{
			t = create_object(&p->plane, OBJ_PLANE);
			world_add_back(w, t, OBJ_PLANE);
		}
		p = p->next;
	}
	parse_free_objects(o);
}

/**
 * @brief Frees all obj structs in world
 *
 * @param world world struct
 */
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

void	setup_cam_init(t_setup_cam *s)
{
	s->center = create_vec3(0, 0, 0);
	s->fov = 0;
	s->norm_vector = create_vec3(0, 0, 0);
}

void	get_setup_cam(t_setup_cam *s, t_objects *objs)
{
	while (objs)
	{
		if (objs->type == OBJ_SETUP_CAM)
		{
			s->center = objs->cam_setup.center;
			s->norm_vector = objs->cam_setup.norm_vector;
			s->fov = objs->cam_setup.fov;
			return ;
		}
		objs = objs->next;
	}
}

int	reload_scene(t_rt *win)
{
	t_objects	*objs;
	t_setup_cam	s;
	t_world		world;

	world.objs = NULL;
	setup_cam_init(&s);
	objs = parse("test.rt");
	if (!objs)
		return (1);
	get_setup_cam(&s, objs);
	parse_world(&world, objs);
	world_free(&win->world);
	win->world = world;
	cam_init(win->cam, win, &s);
	render(win, win->cam, &win->world);
	return (0);
}

/**
 * @brief Checks if a key pressed
 * - If Escape Key is pressed, all malloced data are freed and exit with 0
 *
 * @param key key pressed
 * @param win window data
 * @return returns 0
 */
int	handle_key(int key, t_rt *win)
{
	if (key == XK_Escape)
	{
		world_free(&win->world);
		mlx_dat_free(win->mlx_dat);
		free(win->cam);
		exit(0);
	}
	if (key == XK_r)
	{
		reload_scene(win);
	}
	return (0);
}

/**
 * @brief Frees all malloced data
 *
 * @param win window data
 * @return returns nothing
 */
int	close_all(t_rt *win)
{
	world_free(&win->world);
	mlx_dat_free(win->mlx_dat);
	free(win->cam);
	exit(0);
}

int	parse_and_render(t_rt *rt_dat)
{
	t_cam		*cam;
	t_objects	*objs;
	t_world		world;
	t_setup_cam	s;

	// rt_dat_init(rt_dat);
	world.objs = NULL;
	setup_cam_init(&s);
	// TODO: malloc failure msg
	objs = parse("test.rt");
	if (!objs)
		return (1);
	// Extract camera setup from parsed objects before populating the world
	cam = malloc(sizeof(t_cam));
	get_setup_cam(&s, objs);
	parse_world(&world, objs);
	rt_dat->world = world;
	cam_init(cam, rt_dat, &s);
	rt_dat->cam = cam;
	render(rt_dat, rt_dat->cam, &rt_dat->world);
	return (0);
}

/**
 * @brief The orchestrator
 *
 * @param argc cli argument count
 * @param argv array of cli arguments
 * @return 1 on error, and 0 on normal exit
 */
int	main(int argc, char **argv)
{
	t_rt		rt_dat;


	(void)argc;
	(void)argv;
	rt_dat_init(&rt_dat);
	if (!mlx_dat_init(&rt_dat.mlx_dat))
		return (0); 
	if (parse_and_render(&rt_dat) == 1)
		return (1);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 2, 1L << 0, handle_key, &rt_dat);
	mlx_hook(rt_dat.mlx_dat->mlx_win, 17, 1L << 17, close_all, &rt_dat);
	mlx_loop(rt_dat.mlx_dat->mlx);
	return (0);
}
