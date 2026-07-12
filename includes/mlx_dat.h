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

# define CLOSE 0xCE0E4D0

t_mlx	*mlx_dat_init(t_mlx **mlx_dat);
void	mlx_dat_free(t_mlx *mlx_dat);

void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);

int		handle_key(int key, t_rt *win);
int		close_all(t_rt *win);
void	world_free(t_world *world);

#endif
