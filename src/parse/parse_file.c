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
	return (TRUE);
}

char	*read_rt_file(char *filename)
{
	int		fd;
	int		rd;
	char	buffer[BUF_SIZE];
	char	*res;

	fd = open(filename, O_RDONLY);
	res = NULL;
	if (fd == -1)
		return (NULL);
	while ((rd = read(fd, buffer, BUF_SIZE)))
	{
		buffer[rd] = '\0';
		res = ft_strjoin(res, buffer);
	}
	return (res);
}

t_objects *parse_object(char *s)
{
	int			i;
	char		**res;
	t_objects	*o_res;

	res = ft_split(s, '\n');
	o_res = malloc(sizeof(t_objects));
	if (!o_res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		// if (res[i][1] == 'A' && res[i][0] == 32)
		// 	parse_ambient(res[i], o_res);
	}
	free_str_arr(res);
	return (NULL);
}
