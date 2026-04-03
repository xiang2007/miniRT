/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:09:42 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/24 14:34:02 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3.h"
#include "camera.h"
#include "render.h"
#include "mlx_dat.h"
#include <mlx.h>
#include <stdlib.h>

t_rt	*rt_dat_init(t_rt **rt_dat)
{
	t_rt	*r;

	r = malloc(sizeof(t_rt));
	if (!r)
		return (NULL);
	r->aspect_ratio = (double)16 / 9;
	r->img_w = WIDTH;
	r->img_h = WIDTH / r->aspect_ratio;
	if (r->img_h < 1)
		r->img_h = 1;
	*rt_dat = r;
	if (!mlx_dat_init(&(*rt_dat)->mlx_dat))
	{
		free(*rt_dat);
		return (NULL);
	}
	return (*rt_dat);
}

void	rt_dat_free(t_rt *rt_dat)
{
	mlx_dat_free(rt_dat->mlx_dat);
	free(rt_dat);
}

int	main(int argc, char **argv)
{
	t_cam	cam;
	t_rt	*rt_dat; // TODO: should be malloc or not?

	(void)argc;
	(void)argv;
	// TODO: .rt parser
	if (!rt_dat_init(&rt_dat))
		return (1); // TODO: error msg: malloc failure
	cam_init(&cam, rt_dat);
	render(rt_dat, &cam);
	// TODO: renderer
	mlx_loop(rt_dat->mlx_dat->mlx);
	rt_dat_free(rt_dat);
	return (0);
}
