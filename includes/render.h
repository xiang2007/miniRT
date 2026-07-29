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

void	render(t_rt *rt_dat, t_cam *c, t_world *world);

#endif
