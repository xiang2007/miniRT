/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 23:52:27 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/02/13 23:53:15 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_len(int **matrix)
{
	int	len;

	if (!matrix)
		return (-1);
	len = 0;
	while (matrix[len])
		len++;
	return (len);
}