#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/parse.h"
#define TRUE 1
#define FALSE 0

int	main(int ac, char **av)
{
	(void)ac;
	int	i = 0;
	while(av[i + 1])
		i++;
	printf("%d\n", i);
	return (0);
}