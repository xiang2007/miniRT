/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:12:35 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/07/14 14:18:07 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/ray.h"
#include "../includes/mlx_dat.h"
#include "../includes/objects.h"
#include "../includes/color.h"

t_color light_color(double u, double v, const t_point3 *p)
{
	return(create_color(0, 0, 0));
}




