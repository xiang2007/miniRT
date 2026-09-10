/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:53 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/03 16:15:45 by wshou-xi         ###   ########.fr       */
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

int	parse_check_type(char *s)
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
	const t_parser_fn	parsers[] = {parse_ambient, parse_cam, parse_sphere,
		parse_plane, parse_cylinder, parse_light, NULL, parse_cone};
	int					type;

	type = parse_check_type(s);
	if (type < 0 || type >= (int)(sizeof(parsers)
		/ sizeof(parsers[0])) || !parsers[type])
		return (FALSE);
	return (parsers[type](id, s, o));
}
