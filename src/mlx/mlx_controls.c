/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:19:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/08/29 11:23:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include "mlx_dat.h"
#include "color.h"
#include "../../mlx_Linux/mlx.h"

static void	draw_selection(t_rt *rt, int x, int y)
{
	char		buf[32];
	const char	*objs[] = {"Ambient", "Camera", "Sphere", "Plane",
		"Cylinder", "Light", "Cam_setup", "Cone"};

	if (rt->sel_obj)
	{
		y += 22;
		snprintf(buf, sizeof(buf), "Selected: %s (id: %i)",
			objs[rt->sel_obj->type], rt->sel_obj->id);
		mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
			x, y, 0xFFD700, buf);
	}
}

static const char	*control_text(int i)
{
	const char	*controls[] = {
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

	return (controls[i]);
}

static int	draw_control_list(t_rt *rt, int x, int y)
{
	int			i;

	i = 0;
	while (control_text(i))
	{
		y += 22;
		mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
			x, y, 0xBBBBBB, (char *)control_text(i));
		i++;
	}
	return (y);
}

void	draw_controls(t_rt *rt)
{
	char	buf[32];
	int		x;
	int		y;

	x = rt->img_w + 14;
	y = 22;
	mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
		x, y, 0xFFFFFF, "CONTROLS");
	y = draw_control_list(rt, x, y);
	y += 22;
	snprintf(buf, sizeof(buf), "Render: %.2f s", rt->render_time);
	mlx_string_put(rt->mlx_dat->mlx, rt->mlx_dat->mlx_win,
		x, y, 0xFFD700, buf);
	draw_selection(rt, x, y);
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
