/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:48:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/21 20:01:38 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H


#include "vec3.h"
#include "objects.h"
#include <math.h>

typedef struct s_objects t_objects;

typedef struct s_bvh
{
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_objects		*o;
	t_aabb			box;
}				t_bvh;

t_aabb	build_box(t_objects *o);
t_aabb	surround_box(t_aabb a, t_aabb b);
t_bvh	*build_bvh(t_objects **objects, int start, int end);
bool	hit_bvh(t_bvh *node, t_ray *ray, double max_t, t_hit_dat *rec);
bool	aabb_hit(t_aabb *box, t_ray *ray, double t_min, double t_max);
int		bvh_size(t_objects **obj);
void	free_bvh(t_bvh *node);

#endif