/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/03 16:15:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_objects	*discard_scene(int fd, char *line, t_objects *objects)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (parse_error("Invalid scene description", objects, NULL));
}

t_objects	*parse_object(int fd)
{
	char		*line;
	int			i;
	t_objects	*o_res;

	o_res = NULL;
	i = 0;
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (parse_object_switch(i, line, &o_res) == FALSE)
		{
			return (discard_scene(fd, line, o_res));
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (free(line), o_res);
}
