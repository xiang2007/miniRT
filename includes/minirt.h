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

typedef double t_d;

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

typedef struct s_matrix
{
	int	**matrix;
	int	col;
	int	row;
}				t_matrix;

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

//Mlx functions
void	init_mlx(t_mlx *m);
void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);
int		close_all(t_mlx *data);

//Matrix function
int			matrix_len(int **matrix);
int			compare_matrix(t_matrix *m1, t_matrix *m2);
t_matrix	*create_matrix(int row, int col);
void		free_matrix(t_matrix *m);

#endif