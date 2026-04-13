#include "parse.h"

int	parse_ambient(char *res, t_objects **obj)
{
	char		**s;
	t_obj_type	type;
	t_objects	*o;

	if (!(res[0] == 'A' && res[1] == 32))
		return FALSE;
	type = OBJ_AMBIENT;
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	if (check_ambient_lightning(res) == FALSE)
		return (FALSE);
	s = ft_split(res, ' ');
	o->ambient.ratio = ft_atof(s[1]);
	o->ambient.color = parse_color(s[2]);
	obj_add_back(o, obj);
	return (TRUE);
}
