/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:40:37 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/06/11 02:35:27 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"
#include <math.h>

// TODO: change name from vec to vec3

/**
 * @brief Calculates the sum of the squares of all three components
 *
 * @param a the vector
 * @return the sum
 */
double	vec_len_sq(t_vec3 a)
{
	return (pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0));
}

/**
 * @brief Calculates the vector length using pythagoras theorem
 *
 * @param a the vector
 * @return the vector length
 */
double	vec_len(t_vec3 a)
{
	return (sqrt(vec_len_sq(a)));
}

/**
 * @brief Calculates the surface normal of polygon with two edge vectors
 *
 * @param a the first edge vector
 * @param b the second edge vector
 * @return the surface normal vector
 */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

/**
 * @brief Calculates the scalar dot product of two vectors.
 * // TODO: additional info?
 *
 * @param a the first vector
 * @param b the second vector
 * @return a double representing the scalar dot product
 */
double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * @brief Normalize vector into a Unit Vector that has a magnitude of 1.0
 *
 * @param a the vector
 * @return the unit vector
 */
t_vec3	unit_vec(t_vec3 a)
{
	return (vec_div(a, vec_len(a)));
}
