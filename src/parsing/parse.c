#include "../includes/parse.h"

t_parse	*parse(char *file)
{
	char	*file_content;

	if (check_rt_file(file) == FALSE)
		return (NULL);
	file_content = read_rt_file(file);
	if (file_content == NULL)
		return (NULL);
}

