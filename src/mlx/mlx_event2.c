/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:19:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:23:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "ray.h"
#include "minirt.h"
#include "mlx_dat.h"
#include "mlx.h"
#include "parse.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "color.h"

void	rotate_axis_key(int key, t_vec3 *axis, double *angle)
{
	*axis = create_vec3(0, 0, 0);
	*angle = 0;
	if (key == XK_Left)
	{
		*axis = create_vec3(0, 1, 0);
		*angle = -0.1;
	}
	else if (key == XK_Right)
	{
		*axis = create_vec3(0, 1, 0);
		*angle = 0.1;
	}
	else if (key == XK_Up)
	{
		*axis = create_vec3(1, 0, 0);
		*angle = -0.1;
	}
	else if (key == XK_Down)
	{
		*axis = create_vec3(1, 0, 0);
		*angle = 0.1;
	}
}

static t_ray	click_ray(t_rt *win, int x, int y)
{
	t_vec3	px_sample;
	t_vec3	dir;

	px_sample = vec3_add(win->cam->px00_loc,
			vec3_add(vec3_mul(win->cam->px_delta_u, (double)x),
				vec3_mul(win->cam->px_delta_v, (double)y)));
	dir = vec3_sub(px_sample, win->cam->cam_center);
	return (ray(win->cam->cam_center, dir));
}

int	mouse_select(int button, int x, int y, t_rt *win)
{
	t_ray		r;
	t_hit_dat	rec;

	if (button != 1 || !win->cam || x >= win->img_w)
		return (0);
	r = click_ray(win, x, y);
	rec = (t_hit_dat){0};
	if (scene_intersect(&r, &win->world, &rec) && rec.hit_obj)
	{
		win->sel_obj = rec.hit_obj;
		// printf("Clicked object selected: id(%i) ", win->sel_obj->id);
		// print_object(rec.hit_obj);
	}
	win->key = 1;
	return (0);
}

void	handle_light(t_rt *win)
{
	t_objects	*tmp;

	tmp = win->world.objs;
	while (tmp)
	{
		if (tmp->type == OBJ_LIGHT && win->sel_light_id < tmp->id)
		{
			win->sel_light_id = tmp->id;
			win->sel_obj = tmp;
			return ;
		}
		tmp = tmp->next;
		if (!tmp)
		{
			win->sel_light_id = -1;
			tmp = win->world.objs;
		}
	}
}

void	handle_sel_object(t_rt *win)
{
	t_objects	*tmp;

	tmp = win->world.objs;
	while (tmp)
	{
		if (tmp->type != OBJ_LIGHT && tmp->type != OBJ_AMBIENT && tmp->type != OBJ_SETUP_CAM && tmp->type != OBJ_CAMERA && win->sel_object_id < tmp->id)
		{
			win->sel_object_id = tmp->id;
			win->sel_obj = tmp;
			return ;
		}
		tmp = tmp->next;
		if (!tmp)
		{
			win->sel_object_id = -1;
			tmp = win->world.objs;
		}
	}	
}

static const char	*g_controls[] = {
	"ESC           quit",
	"LMB           select object under cursor",
	"F             select camera",
	"R             select light by loop",
	"V             select object by loop",
	"",
	"ARROWS        rotate camera or object around X & Y",
	"-  =          shrink / expand sphere",
	"",
	"W A S D       move camera or object",
	"Q E           move camera or object (down/up)",
	"Z             full quality",
	"C             toggle checker",
	NULL
};

void	draw_controls(t_rt *rt)
{
	char	buf[32];
	int		x;
	int		y;
	int		i;
	const char	*objs[] = {"Ambient", "Camera", "Sphere", "Plane",
		"Cylinder", "Light", "Cam_setup", "Cone"};
	
	x = rt->img_w + 14;
	y = 22;
	mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
		x, y, 0xFFFFFF, "CONTROLS");
	i = 0;
	while (g_controls[i])
	{
		y += 22;
		mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
			x, y, 0xBBBBBB, (char *)g_controls[i]);
		i++;
	}
	y += 22;
	snprintf(buf, sizeof(buf), "Render: %.2f s", rt->render_time);
	mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
		x, y, 0xFFD700, buf);
	if (rt->sel_obj)
	{
		y += 22;
		snprintf(buf, sizeof(buf), "Selected: %s (id: %i)", objs[rt->sel_obj->type], rt->sel_obj->id);
		mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
			x, y, 0xFFD700, buf);			
	}
}

void	handle_toggle_checker(t_rt *win)
{
	t_lambertian	*lam;
	t_objects		*o;

	o = win->sel_obj;
	if (!o || o->type != OBJ_PLANE)
		return ;
	lam = (t_lambertian *)o->plane.material;
	if (!lam || lam->base.scatter != lambertian_scatter)
		return ;
	if (lam->checker_size > 0.0)
		lam->checker_size = 0.0;
	else
	{
		lam->checker_size = 1.0;
		lam->checker_color = create_color(1.0, 1.0, 1.0);
	}
}
