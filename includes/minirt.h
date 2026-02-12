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

typedef double t_d;


typedef struct	s_tuple
{
	t_d	x;
	t_d	y;
	t_d	z;
	int	flag;
}				t_tuple;

#endif