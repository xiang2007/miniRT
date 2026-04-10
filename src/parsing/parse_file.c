#include "../includes/parse.h"

int	check_rt_file(char *file_name)
{
	int			i;
	char*		t;
	const char*	f = ".rt";

	i = 0;
	while (file_name[i] && file_name[i] != '.')
		i++;
	t = file_name + i;
	if (ft_strcmp(t, f) == FALSE)
		return (FALSE);
	return (FALSE);
}

char	*read_rt_file(char *filename)
{
	int		fd;
	int		rd;
	char	*buffer;
	char	*res;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ((rd = read(fd, buffer, 10)))
	{
		buffer[rd] = '\0';
		res = ft_strjoin(buffer, res);
	}
	return (res);
}

t_parse	count_object(char *fc)
{
	int	i;

	i = 0;
	while(fc[i] || fc[i] == ' ' || fc[i] == '\t')
	{
		if (fc[i] == 'A' && fc[i + 1] == ' ')
			
	}
}
