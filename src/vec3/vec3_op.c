/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshou-xi <wshou-xi@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:21:02 by wshou-xi          #+#    #+#             */
/*   Updated: 2026/03/12 13:55:45 by wshou-xi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"

/**
 * @brief Adds both vector
 * The differences are calculated for each independent dimension
 *
 * @param a the first vector
 * @param b the second vector
 * @return the resultant vector
 */
t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/**
 * @brief Subtracts both vector
 * - The differences are calculated for each independent dimension
 *
 * @param a the first vector
 * @param b the second vector
 * @return the resultant vector
 */
t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

/**
 * @brief Multiplies a vector with a scalar
 *
 * @param a the vector
 * @param t the scalar
 * @return the resultant vector
 */
t_vec3	vec_mul(t_vec3 a, double t)
{
	t_vec3	res;

	res.x = a.x * t;
	res.y = a.y * t;
	res.z = a.z * t;
	return (res);
}

/**
 * @brief Divides a vector with a scalar
 *
 * @param a the vector
 * @param t the scalar
 * @return the resultant vector
 */
t_vec3	vec_div(t_vec3 a, double t)
{
	t_vec3	res;
	double	inv;

	inv = (1.0 / t);
	res.x = a.x * inv;
	res.y = a.y * inv;
	res.z = a.z * inv;
	return (res);
}

/**
 * @brief Creates a vector struct with numbers from the parameter
 *
 * @param a the x coordinate
 * @param b the y coordinate
 * @param c the z coordinate
 * @return the vector
 */
t_vec3	create_vec3(double a, double b, double c)
{
	t_vec3	res;

	res.x = a;
	res.y = b;
	res.z = c;
	return (res);
}
