#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include "minirt.h"
# include "libft.h"
# define TRUE 1
# define FALSE 0

typedef struct s_parse
{
	int	ambient;
	int	camera;
	int	cylinder;
	int	light;
	int	sphere;
	int	plane;
}		t_parse;

int		check_rt_file(char *file_name);
char	*read_rt_file(char *filename);


#endif