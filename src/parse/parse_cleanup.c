/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:11:16 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/15 00:34:35 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threadpool.h"
#include "../../includes/parse.h"

void	free_str_arr(char **strarr)
{
	int	i;

	if (!strarr)
		return ;
	i = 0;
	while (strarr[i])
		free(strarr[i++]);
	free(strarr);
}

void	parse_free_objects(t_objects *o)
{
	t_objects	*next;

	while (o)
	{
		next = o->next;
		free_object_material(o);
		free(o);
		o = next;
	}
}

t_objects	*parse_error(char *msg, t_objects *o, char **strarr)
{
	if (msg)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	parse_free_objects(o);
	free_str_arr(strarr);
	return (NULL);
}
