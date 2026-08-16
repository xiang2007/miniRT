/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:19:00 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/29 17:33:34 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "ray.h"
# include "threadpool.h"

typedef struct s_spp
{
	t_color	cl;
	t_vec3	offset;
	t_vec3	px_sample;
	t_vec3	r_dir;
	t_world	*w;
	t_cam	*c;
	t_ray	r;
	int		h;
	int		max_bounce_depth;
	int		spp;
	double	pss;
}				t_spp;

// void	render(t_rt *rt_dat, t_cam *c, t_world *world);
void	render_row(t_tile tile, t_spp spp, int y, t_rt *rt_dat);
t_color	spp_loop(t_spp spp, int n);

#endif
