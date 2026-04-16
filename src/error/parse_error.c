/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:13:51 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/04/16 16:49:32 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/error.h"

void	error_no_input(void)
{
	printf("%s\n", "No input file './miniRT `*.rt`'");
}

void	error_invalid_file(char	*filename)
{
	int		fd;
	int		rd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Invalid file: %s\n", filename));
	rd = read(fd, buffer, 1);
	if (!buffer[0])
		return (printf("Empty file\n"));
	
}

void	error(t_error_type type, t_obj_type o)
{
	if (type == ERR_NO_INPUT)
		error_no_input(void);
}