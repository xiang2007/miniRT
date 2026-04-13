#include <stdio.h>
#include "../libft/libft.h"
#include "../includes/parse.h"
#define TRUE 1
#define FALSE 0

int	check_ambient_lightning(char *s)
{
	int		i;
	double	temp;
	char	**t1;
	char	**t2;

	t1 = ft_split(s, ' ');
	if (!check_float(t1[1]))
		return (FALSE);
	temp = ft_atof(t1[1]);
	if (temp < 0 || temp > 1)
		return (free_str_arr(t1), FALSE);
	if (!check_color(t1[2]))
		return (free_str_arr(t1), FALSE);
	t2 = ft_split(t1[2], ',');
	i = 0;
	while(t2[i])
	{
		temp = ft_atoi(t2[i]);
		if (temp < 0 || temp > 255)
			return (free_str_arr(t1), free_str_arr(t2), FALSE);
		i++;
	}
	return (free_str_arr(t1), free_str_arr(t2), TRUE);
}

int	main(int ac, char **av)
{
	(void)ac;
	printf("flag: %d\n", check_ambient_lightning(av[1]));
	return (0);
}