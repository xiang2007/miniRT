/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_object2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:23:49 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 16:12:04 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

int	parse_arg_count(char **arg)
{
	int	size;

	size = 0;
	if (!arg || !*arg)
		return (-1);
	while (arg[size])
	{
		if (!arg[size][0])
			return (-1);
		size++;
	}
	return (size);
}

int	parse_cylinder(char *s, t_objects **obj)
{
	char		**res;
	t_objects	*o;

	if (!check_cylinder(s))
		return (FALSE);
	res = ft_split(s, ' ');
	if (!res)
		return (FALSE);
	o = malloc(sizeof(t_objects));
	if (!o)
		return (FALSE);
	o->type = OBJ_CYLINDER;
	o->cylinder.center = parse_cords(res[1]);
	o->cylinder.axis = parse_cords(res[2]);
	o->cylinder.radius = ft_atof(res[3]);
	o->cylinder.height = ft_atof(res[4]);
	o->cylinder.color = parse_color(res[5]);
	if (o->cylinder.color.r == -1)
		return (free(o), free_str_arr(res), FALSE);
	free_str_arr(res);
	obj_add_back(o, obj);
	return (TRUE);
}

void	print_objects(t_objects *o)
{
	t_objects	*p;

	if (!o)
		return ;
	p = o;
	while(p)
	{
		printf("type: %d\n", p->type);
		p = p->next;
	}
}
