/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_dat.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydylan-k <ydylan-k@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:16:06 by ydylan-k          #+#    #+#             */
/*   Updated: 2026/04/02 18:16:06 by ydylan-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DAT_H
# define MLX_DAT_H

t_mlx	*mlx_dat_init(t_mlx **mlx_dat);
void	mlx_dat_free(t_mlx *mlx_dat);

void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);

#endif
