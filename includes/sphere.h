/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:54:06 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/03 15:54:06 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

/**
 * @brief point is used as the center of the sphere
 */
typedef struct s_sphere
{
	t_point3	point;
	double		radius;
}				t_sphere;

#endif
