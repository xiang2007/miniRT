/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:38:54 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/02 22:38:54 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int		rgb_to_hex(int r, int g, int b);

int		color_get_hex(t_color c);
t_color	color_mul_n(t_color c, double n);
t_color	color_mul(t_color a, t_color b);
t_color	color_add(t_color a, t_color b);
t_color	create_color(double r, double g, double b);

#endif
