/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 16:08:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

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
	rd = read(fd, buffer, BUF_SIZE);
	while (rd > 0)
	{
		buffer[rd] = '\0';
		res = ft_strjoin(res, buffer);
		rd = read(fd, buffer, BUF_SIZE);
	}
	return (res);
}

t_obj_type	parse_check_type(char *s)
{
	if (!s || !s[0])
		return (-1);
	if (s[0] == 'A')
		return (OBJ_AMBIENT);
	else if (s[0] == 'C')
		return (OBJ_CYLINDER);
	else if (s[0] == 'L')
		return (OBJ_LIGHT);
	else if (!ft_strncmp(s, "sp", 2))
		return (OBJ_SPHERE);
	else if (!ft_strncmp(s, "pl", 2))
		return (OBJ_PLANE);
	else if (!ft_strncmp(s, "cy", 2))
		return (OBJ_CYLINDER);
	return (-1);
}

int	parse_object_switch(char *s, t_objects **o)
{
	t_obj_type	type;

	type = parse_check_type(s);
	if (type == OBJ_AMBIENT)
		return (parse_ambient(s, o));
	else if (type == OBJ_CAMERA)
		return (parse_cam(s, o));
	else if (type == OBJ_CYLINDER)
		return (parse_cylinder(s, o));
	else if (type == OBJ_LIGHT)
		return (parse_light(s, o));
	else if (type == OBJ_PLANE)
		return (parse_plane(s, o));
	else if (type == OBJ_SPHERE)
		return (parse_sphere(s, o));
	return (FALSE);
}

t_objects *parse_object(char **res)
{
	int			i;
	t_obj_type	type;
	t_objects	*o_res;

	o_res = malloc(sizeof(t_objects));
	if (!o_res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		type = parse_check_type(res[i]);
		if (parse_object_switch(res[i], type) == FALSE)
			return ()
	}
	free_str_arr(res);
	return (NULL);
}
