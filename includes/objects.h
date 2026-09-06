/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:49:56 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/08/29 10:42:11 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vec3.h"
# include "material.h"

typedef struct s_rt			t_rt;
typedef struct s_bvh		t_bvh;
typedef struct s_objects	t_objects;

/* vtable types — contract v1 */
typedef struct s_ray		t_ray;
typedef struct s_hit_dat	t_hit_dat;

typedef double	(*t_hit_fn)(struct s_objects *self, struct s_ray *ray, double r_max, struct s_hit_dat *rec);
typedef void	(*t_translate_fn)(struct s_objects *self, int key);
typedef void	(*t_rotate_fn)(struct s_objects *self, int key);

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
	OBJ_SETUP_CAM,
	OBJ_CONE
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
	t_vec3		axis;
	t_color		color;
	t_material	*material;
}				t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;
	t_material	*material;
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
	t_color		color;
}				t_light;

typedef struct s_setup_cam
{
	double		fov;
	t_point3	center;
	t_vec3		norm_vector;
}				t_setup_cam;

typedef struct s_cone
{
	t_vec3		pos;
	t_vec3		axis;
	double		radius;
	double		height;
	t_color		color;
	double		constant_k;
	t_material	*material;
}				t_cone;

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

struct s_objects
{
	int				id;
	t_obj_type		type;
	t_aabb			box;
	t_hit_fn		hit;        /* contract v1: non-NULL for sp/pl/cy/co */
	t_translate_fn	translate;  /* contract v1: non-NULL for sp/pl/cy/co/L */
	t_rotate_fn		rotate;     /* contract v1: non-NULL for cy/pl/co */
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_ambient	ambient;
		t_cam		cam;
		t_light		light;
		t_cone		cone;
		t_setup_cam	cam_setup;
	};
	t_objects	*next;
};

typedef struct s_cylinder_hit
{
	t_vec3	x;
	t_vec3	p;
	t_vec3	half_axis;
	t_vec3	top_center;
	t_vec3	bot_center;
	t_vec3	neg_axis;
	t_vec3	outward_normal;
	double	a;
	double	b;
	double	c;
	double	d;
	double	root;
	double	m;
	double	d_dot_v;
	double	x_dot_v;
	double	t_tube;
	double	t_top;
	double	t_bot;
	double	t_best;
}				t_cylinder_hit;

typedef struct s_hit_sphere
{
	t_vec3	ori_center;
	t_vec3	outward_normal;
	double	a;
	double	h;
	double	c;
	double	d;
	double	root;
}			t_sphere_hit;

typedef struct s_world
{
	t_objects	*objs;
	t_objects	**bvh_obj;
	t_bvh		*bvh;
}	t_world;

// Objects function
int			obj_bvh_count(t_objects *o);
void		free_object_material(t_objects *o);
void		obj_add_back(t_objects *src, t_objects **dest);
t_objects	*create_object(t_objects *o);
t_objects	*select_object(int key, t_world *world);
t_objects	**obj2arr(t_objects *o);
void		toggle_checker(t_objects *sel);

// Object move function
void		cylinder_translate(t_objects *self, int key);
void		sphere_translate(t_objects *self, int key);
void		plane_translate(t_objects *self, int key);
void		light_translate(t_objects *self, int key);
void		cone_translate(t_objects *self, int key);
void		move_objects(int key, t_objects **obj);
void		lower_res(int key, t_rt *rt);
void		reset_res(t_rt *rt);
// World function
void		world_add_back(t_world *world, t_objects *obj, t_obj_type type);

void	set_face_normal(const t_ray *r, const t_vec3 *out_norm, t_hit_dat *rec);

double	plane_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec);
double	sphere_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec);
double	cylinder_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec);
double	cone_hit(t_objects *self, t_ray *ray, double r_max, t_hit_dat *rec);

void	plane_rotate(t_objects *self, int key);
void	cylinder_rotate(t_objects *self, int key);
void	cone_rotate(t_objects *self, int key);

#endif
