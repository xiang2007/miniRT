/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:49:56 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/11 17:33:10 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
typedef enum e_obj_type
{
	OBJ_AMBIENT,
	OBJ_CAMERA,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}			t_obj_type;

/**
 * @brief point is used as the center of the sphere
 */
typedef struct s_sphere
{
	t_point3	point;
	double		radius;
}				t_sphere;

typedef struct s_plane
{
	t_point3	center;
	t_vec3		normal;
	int			color;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	int			color;
}				t_cylinder;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}				t_ambient;

typedef struct s_cam
{
	t_point3	cords;
	t_vec3		normalized;
	int			fov;
}				t_cam;

typedef struct s_objects
{
	t_obj_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_ambient	ambient;
		t_cam		cam;
	};
	struct s_objects	*next;
}				t_objects;

typedef struct s_world
{
	t_objects	*objs;
}	t_world;

t_sphere	sphere(t_point3 center, double radius);

#endif
