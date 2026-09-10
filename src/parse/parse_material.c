/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:36:40 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/09/04 12:40:03 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_material	*parse_optional_material(char **res, int idx, t_color color)
{
	if (res[idx])
		return (parse_mat_switch(res, idx, color, 0));
	return (create_lambertian(color));
}
