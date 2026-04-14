#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/parse.h"
#define TRUE 1
#define FALSE 0

int	main(int ac, char **av)
{
	(void)ac;
	printf("flag: %d\n", ft_strncmp(av[1], "pl", 2));
	return (0);
}