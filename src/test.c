#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/parse.h"
#define TRUE 1
#define FALSE 0

int	main(int ac, char **av)
{
	(void)ac;
	printf("flag: %d\n", check_norm_vector(av[1]));
	return (0);
}