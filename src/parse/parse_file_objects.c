#include "parse.h"

int	parse_ambient(char *res, t_objects **obj)
{
	char		**s_arr;
	t_obj_type	type;
	t_ambient	*a;

	if (!(res[0] == 'A' && res[1] == 32))
		return FALSE;
	type = OBJ_AMBIENT;
	a = malloc(sizeof(t_ambient));
	if (!a)
		return (FALSE);
	s_arr = ft_split(res, ' ');
	if (!s_arr)
		return (free(a), FALSE);
	if (check_float(s_arr[1]) == FALSE)
		return (free_str_arr(s_arr), free(a), FALSE);
	a->ratio = ft_atof(s_arr[1]);
	if (a->ratio < 0 || a->ratio > 1)
		return (free_str_arr(s_arr), free(a), FALSE);
	a->color = parse_color(s_arr[2]);
	if (a->color.r == -1 || a->color.g == -1 || a->color.b == -1)
		return (free_str_arr(s_arr), free(a), FALSE);
}