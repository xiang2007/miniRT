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

#include "ray.h"
#include "../../includes/minirt.h"
#include "../../includes/mlx_dat.h"
#include "../../mlx_Linux/mlx.h"
#include "parse.h"
#include <X11/keysym.h>
#include <stdio.h>
#include "color.h"

void	rotate_axis_key(int key, t_vec3 *axis, double *angle)
{
	*axis = create_vec3(0, 0, 0);
	*angle = 0;
	if (key == XK_bracketleft)
	{
		*axis = create_vec3(0, 1, 0);
		*angle = -0.1;
	}
	else if (key == XK_bracketright)
	{
		*axis = create_vec3(0, 1, 0);
		*angle = 0.1;
	}
	else if (key == XK_semicolon)
	{
		*axis = create_vec3(1, 0, 0);
		*angle = -0.1;
	}
	else if (key == XK_apostrophe)
	{
		*axis = create_vec3(1, 0, 0);
		*angle = 0.1;
	}
}

static t_ray	click_ray(t_rt *win, int x, int y)
{
	t_vec3	px_sample;
	t_vec3	dir;

	px_sample = vec_add(win->cam->px00_loc,
			vec_add(vec_mul(win->cam->px_delta_u, (double)x),
				vec_mul(win->cam->px_delta_v, (double)y)));
	dir = vec_sub(px_sample, win->cam->cam_center);
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
	if (hit_list(&r, &win->world, &rec) && rec.hit_obj)
	{
		win->sel_obj = rec.hit_obj;
		printf("Clicked object selected: ");
		print_object(rec.hit_obj);
	}
	return (0);
}

static const char	*g_controls[] = {
	"ESC           quit",
	"R             reload scene",
	"0-9           select object by id",
	"LMB           select under cursor",
	"",
	"ARROWS        move selected object",
	"-  =          shrink / expand sphere",
	"[  ]          rotate around Y",
	";  '          rotate around X",
	"",
	"W A S D       move camera",
	"Q E           move camera (down/up)",
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

	if (!rt->show_controls)
		return ;
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
	queue_render(win);
}
