/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:48:28 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/18 11:35:00 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H


#include "vec3.h"
#include "objects.h"
#include "minirt.h"

typedef struct s_aabb
{
	t_point3	min;
	t_point3	max;
}				t_aabb;

typedef struct s_bvh
{
	t_objects		o;
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_objects		*o;
	t_aabb			box;
}				t_bvh;

t_aabb build_box(t_objects *o);

#endif