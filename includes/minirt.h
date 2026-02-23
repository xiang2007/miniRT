#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx_Linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# define EP 1e-9
# define WIDTH 800
# define HEIGHT 800
# define PI 3.14159265358979323846

typedef double t_d;

typedef enum	e_object
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	CAMERA
}	t_object;

typedef struct	s_tuple
{
	t_d	x;
	t_d	y;
	t_d	z;
	t_d	w;
}				t_tuple;

typedef struct	s_color
{
	t_d	red;
	t_d	green;
	t_d	blue;
}				t_color;

typedef struct	s_matrix
{
	t_d	**matrix;
	int	col;
	int	row;
}				t_matrix;

typedef struct	s_ray
{
	t_tuple	*origin;
	t_tuple	*direction;
}				t_ray;

typedef struct s_cylinder
{
	t_d					x;
	t_d					y;
	t_d					z;
	t_d					dia;
	t_d					height;
	t_color				*c;
	t_tuple				*norm;
	t_matrix			*transform;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct	s_plane
{
	t_d					x;
	t_d					y;
	t_d					z;
	t_color				*c;
	t_tuple				*norm;
	t_matrix			*transform;
	struct s_plane		*next;
}				t_plane;

typedef struct	s_light
{
	t_d					x;
	t_d					y;
	t_d					z;
	int					fov;
	t_matrix			*norm;
	t_matrix			*transform;
	struct s_light		*next;
}				t_light;

typedef struct	s_sp
{
	t_d			diameter;
	t_tuple		*origin;
	t_color		*c;
	t_matrix	*transform;
	struct s_sp	*next;
}				t_sp;

typedef struct	s_al
{
	t_d		ratio;
	t_color	*c;
	struct s_al	*next;
}				t_al;

typedef struct	s_cam
{
	int			fov;
	t_d			x;
	t_d			y;
	t_d			z;
	t_tuple		*norm;
	t_matrix	*transform;
}				t_cam;

typedef struct	s_obj
{
	int			id;
	t_sp		*sphere;
	t_al		*ambient_lightning;
	t_cam		*cam;
	t_plane		*plane;
	t_cylinder	*cy;
	t_object	type;

}				t_obj;

typedef struct	s_intersect
{
	t_d					t;
	t_sp				*object;
	struct s_intersect	*next;
}				t_intersect;

typedef struct	s_mlx
{
	void	*img;
	void	*addr;
	void	*mlx;
	void	*mlx_win;
	int		bpp;
	int		line_length;
	int		endian;
}				t_mlx;

// Math functions
t_d	sq(t_d n);

//Tuple functions
t_tuple	*create_vector(t_d x, t_d y, t_d z);
t_tuple	*create_point(t_d x, t_d y, t_d z);
t_tuple	*add_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*subtract_tuple(t_tuple *t1, t_tuple *t2);
t_tuple	*neg_tuple(t_tuple *t1);
t_tuple	*multiply_tuple(t_d n, t_tuple *t1);
t_tuple	*divide_tuple(t_d n, t_tuple *t1);
t_d		magnitude(t_tuple *t1);
t_tuple	*normalize(t_tuple *t1);
t_d		dot_product(t_tuple *t1, t_tuple *t2);
t_tuple	*cross(t_tuple *t1, t_tuple *t2);
t_tuple	*mult_2_tuple(t_tuple *t1, t_tuple *t2);
void	print_tuple(t_tuple *t);
t_tuple	*sub_free_s2(t_tuple *t1, t_tuple *t2);

//Mlx functions
void	init_mlx(t_mlx *m);
void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);
int		close_all(t_mlx *data);

//Matrix function
t_matrix	*mult_matrix(t_matrix *m1, t_matrix *m2);
int			compare_matrix(t_matrix *m1, t_matrix *m2);
t_matrix	*create_matrix(int row, int col);
void		free_matrix(t_matrix *m);
void		identity_matrix(t_matrix **m);
void		print_mat(t_matrix *m);
t_matrix	*transpose_matrix(t_matrix *m1);
int			determinant(t_matrix *m);
t_matrix	*sub_matrix(t_matrix *m, int row, int col);
t_matrix	*dup_matrix(t_matrix *m);
int			minor_matrix(t_matrix *m, int row, int col);
void		negate(t_matrix *m);
int			cofactor(t_matrix *m1, int row, int col);
t_matrix	*inverse_matrix(t_matrix *m);
void		set_identity_matrix(t_matrix *identity);
t_matrix	*mult_matrix_w_tuple(t_matrix *m1, t_tuple *t);
t_matrix	*mult_free_s2(t_matrix *s1, t_matrix *s2);
t_matrix	*inv_and_free(t_matrix *m);
t_matrix	*dy_mult_free_s2(t_matrix *s1, t_matrix *s2);

// Matrix Translation
t_matrix	*mult_translate_matrix(t_tuple *point, int x, int y, int z);
t_matrix	*dynamic_mult_matrix(t_matrix *m1, t_matrix *m2);
t_matrix	*point_to_matrix(t_tuple *t);
t_matrix	*mult_inv_translate_matrix(t_tuple *point, int x, int y, int z);
t_matrix	*vector_to_matrix(t_tuple *t);
t_matrix	*mult_translation_vector(t_tuple *v, int x, int y, int z);

// Matrix scaling
t_matrix	*scale_to_point(t_tuple *p, int x, int y, int z);
t_matrix	*scale_to_vec(t_tuple *v, int x, int y, int z);
t_matrix	*inv_scale_to_vec(t_tuple *v, int x, int y, int z);
t_matrix	*reflection(t_tuple *p, int x, int y, int z);

// Matrix rotation
t_matrix	*rotation_x(t_d	r);
t_matrix	*rotation_y(t_d	r);
t_matrix	*rotation_z(t_d	r);
t_tuple		*rot_x(t_tuple *p, t_d radian);
t_tuple		*rot_y(t_tuple *p, t_d radian);
t_tuple		*rot_z(t_tuple *p, t_d radian);

// Ray
t_tuple		*postition(t_ray *ray, t_d t);
t_ray		*create_ray(t_tuple *origin_point, t_tuple *direction_vector);
void		free_ray(t_ray *r);
t_intersect	*intersect(t_sp *s, t_ray *ray);
t_intersect	*hit(t_intersect *it);
t_intersect	*intersection(t_d t, t_sp *s);
void		add_intersect(t_intersect *src, t_intersect **dest);
void		print_ray(t_ray *r);
void		print_intersect(t_intersect *t);


// Objects
t_sp	*create_sphere(t_tuple *origin, t_d diameter);
void		set_sphere_color(t_sp *sphere, t_color *color);
t_plane		*create_plane(t_d x, t_d y, t_d z, t_color *c);
void		add_plane_next(t_plane *src, t_plane **dest);
t_obj		*create_object(void);
t_cylinder	*create_cylinder(t_d x, t_d y, t_d z);
void		set_cylinder_argument(t_cylinder *cy, t_d diameter, t_d height, t_color *c);
t_cam		*create_camera(int fov, t_d x, t_d y, t_d z);
t_al		*create_ambient_lightning(t_d ratio, t_color *color);
void		add_ambient_lightning(t_al *src, t_al  **dest);
void		add_cylinder_next(t_cylinder *src, t_cylinder **dest);
void		add_sphere_back(t_sp *src, t_sp **dest);
void		print_sphere(t_sp *s);

// Transformation
t_ray	*transform_ray(t_ray *r, t_matrix *m);
t_ray	*scale_ray(t_ray *r, t_d x, t_d y, t_d z);
t_sp	*sphere_transform(t_sp *s, t_d x, t_d y, t_d z);

// Tuple conversion
t_tuple	*matrix_to_point(t_matrix *m);
t_tuple	*matrix_to_vector(t_matrix *m);

#endif