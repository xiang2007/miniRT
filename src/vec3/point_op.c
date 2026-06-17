/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:27:36 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/05/11 17:40:48 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/**
 * @brief TODO
 *
 * @param p1
 * @param p2
 * @return
 */
t_point3 sub_point(t_point3 p1, t_point3 p2)
{
	t_point3	res;

	res = (t_point3)create_vec3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
	return (res);
}
