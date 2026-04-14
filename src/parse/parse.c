/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:37:21 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/14 14:37:22 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"

t_parse	*parse(char *file)
{
	char	*file_content;

	if (check_rt_file(file) == FALSE)
		return (NULL);
	file_content = read_rt_file(file);
	if (file_content == NULL)
		return (NULL);
	return (NULL);
}
