/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:49:56 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/07/21 20:26:59 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
# include "material.h"

typedef struct s_rt t_rt;
typedef struct s_bvh t_bvh;

typedef struct s_aabb
{
	t_point3	min;
	t_point3	max;
}				t_aabb;

typedef enum e_obj_type
{
	OBJ_AMBIENT,
	OBJ_CAMERA,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_LIGHT,
	OBJ_SETUP_CAM
}			t_obj_type;

/**
 * @brief point is used as the center of the sphere
 */
typedef struct s_sphere
{
	t_point3	point;
	t_color		color;
	double		radius;
	t_material	*material;
}				t_sphere;

typedef struct s_plane
{
	t_point3	center;
	t_vec3		normal;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}				t_ambient;

typedef struct s_light
{
	double		brightness_ratio;
	t_point3	cords;
}				t_light;

typedef struct s_setup_cam
{
	int			fov;
	t_point3	center;
	t_vec3		norm_vector;
}				t_setup_cam;

typedef struct s_cam
{
	int			fov;
	double		vfov;
	double		foc_len;
	double		vp_h;
	double		vp_w;
	double		h;
	t_vec3		cam_center;
	t_vec3		vp_u;
	t_vec3		vp_v;
	t_vec3		px_delta_u;
	t_vec3		px_delta_v;
	t_vec3		vp_upper_left;
	t_vec3		px00_loc;
	t_vec3		u;
	t_vec3		v;
	t_vec3		w;
	t_point3	lookat;
	t_point3	lookfrom;
	t_point3	vup;
}				t_cam;

typedef struct s_objects
{
	int			id;
	t_obj_type	type;
	t_aabb		box;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_ambient	ambient;
		t_cam		cam;
		t_light		light;
		t_setup_cam	cam_setup;
	};
	struct s_objects	*next;
}				t_objects;

typedef struct s_world
{
	t_objects	*objs;
	t_objects	**bvh_obj;
	t_bvh		*bvh;
}	t_world;

// Objects function
int			obj_size(t_objects *o);
int			obj_sphere_count(t_objects *o);
void		obj_add_back(t_objects *src, t_objects **dest);
void		print_object_list(t_objects *o);
t_sphere	sphere(t_point3 center, double radius);
t_objects	*create_object(void *obj, t_obj_type type, int id);
t_objects	*select_object(int key, t_world *world);
t_objects	**Obj2Arr(t_objects *o);

// Object move function
void	*cylinder_mv(int key, t_objects *o);
void	*sphere_mv(int key, t_objects *o);
void	*plane_mv(int key, t_objects *o);
void	move_objects(int key, t_objects **obj);
void	lower_res(int key, t_rt *rt);
void	reset_res(t_rt *rt);


// World function
void	world_add_back(t_world *world, t_objects *obj, t_obj_type type);

#endif
