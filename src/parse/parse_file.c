/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/03 10:40:24 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "threadpool.h"
#include "../../includes/parse.h"

int	check_rt_file(char *file_name)
{
	int			i;
	char		*t;
	const char	*f;

	i = 0;
	f = ".rt";
	while (file_name[i] && file_name[i] != '.')
		i++;
	t = file_name + i;
	if (ft_strcmp(t, f) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	read_rt_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	return (fd);
}

t_obj_type	parse_check_type(char *s)
{
	if (!s || !s[0])
		return (-1);
	if (s[0] == 'A')
		return (OBJ_AMBIENT);
	else if (s[0] == 'C')
		return (OBJ_CAMERA);
	else if (s[0] == 'L')
		return (OBJ_LIGHT);
	else if (!ft_strncmp(s, "sp", 2))
		return (OBJ_SPHERE);
	else if (!ft_strncmp(s, "pl", 2))
		return (OBJ_PLANE);
	else if (!ft_strncmp(s, "cy", 2))
		return (OBJ_CYLINDER);
	else if (!ft_strncmp(s, "co", 2))
		return (OBJ_CONE);	
	return (-1);
}

int	parse_object_switch(int id, char *s, t_objects **o)
{
	t_obj_type	type;

	type = parse_check_type(s);
	if (type == OBJ_AMBIENT)
		return (parse_ambient(id, s, o));
	else if (type == OBJ_CAMERA)
		return (parse_cam(id, s, o));
	else if (type == OBJ_CYLINDER)
		return (parse_cylinder(id, s, o));
	else if (type == OBJ_LIGHT)
		return (parse_light(id, s, o));
	else if (type == OBJ_PLANE)
		return (parse_plane(id, s, o));
	else if (type == OBJ_SPHERE)
		return (parse_sphere(id, s, o));
	else if (type == OBJ_CONE)
		return (parse_cone(id, s, o));
	return (FALSE);
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
		if (!line)
			break ;
		if (parse_object_switch(i, line, &o_res) == FALSE)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (o_res);
}
