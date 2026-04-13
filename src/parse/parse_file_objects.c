#include "parse.h"

int	parse_ambient(char *res, t_objects **obj)
{
	char		**s;
	t_objects	*o;

	if (!res)
		return (FALSE);
	if (!(res[0] == 'A' && res[1] == 32))
		return FALSE;
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	if (check_ambient_lightning(res) == FALSE)
		return (FALSE);
	s = ft_split(res, ' ');
	o->type = OBJ_AMBIENT;
	o->ambient.ratio = ft_atof(s[1]);
	o->ambient.color = parse_color(s[2]);
	obj_add_back(o, obj);
	free_str_arr(s);
	return (TRUE);
}

int	parse_cam(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (s[0] == 'C' && res[1] != 'C')
		return (FALSE);
	if (!check)
	res = ft_split(s, ' ');
	o = malloc(sizeof(t_objects));

}
