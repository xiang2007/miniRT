/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:48:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/28 11:34:13 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

# include "vec3.h"
# include "objects.h"
# include <math.h>

typedef struct s_objects	t_objects;

typedef struct s_bvh
{
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_objects		*o;
	t_aabb			box;
}				t_bvh;

typedef struct s_slab_args
{
	double	origin;
	double	direction;
	double	min;
	double	max;
	double	*t_min;
	double	*t_max;
}			t_slab_args;

t_aabb	build_box(t_objects *o);
t_aabb	surround_box(t_aabb a, t_aabb b);
t_bvh	*build_bvh(t_objects **objects, int start, int end);
bool	hit_bvh(t_bvh *node, t_ray *ray, double max_t, t_hit_dat *rec,
		t_objects *skip);
bool	aabb_hit(t_aabb *box, t_ray *ray, double t_min, double t_max);
int		bvh_size(t_objects **obj);
void	free_bvh(t_bvh *node);
void	swap_double(double *a, double *b);

#endif
