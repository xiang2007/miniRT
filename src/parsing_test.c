#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/parse.h"
#define TRUE 1
#define FALSE 0

int	main(int ac, char **av)
{
	t_objects	*o;

	(void)ac;
	o = parse(av[1]);
	if (!o)
		return (1);
	print_objects(o);
	parse_free_objects(o);
	return (0);
}