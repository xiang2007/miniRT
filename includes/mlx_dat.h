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
int		mlx_dat_free(t_mlx *mlx_dat);

void	mlx_put_pixel(t_mlx *m, int x, int y, int color);
void	mlx_put_to_window(t_mlx *m);

int		handle_key(int key, t_rt *win);
int		close_all(t_rt *win);
void	world_free(t_world *world);

void	rebuild_world_bvh(t_world *world);

int		mouse_select(int button, int x, int y, t_rt *win);

void	draw_controls(t_rt *rt);
void	mlx_swap_buffers(t_mlx *m);

void	handle_light(t_rt *win);
void	handle_sel_object(t_rt *win);

void	keymap(int key, t_rt *dat);

int		mlx_render_loop(void *param);
void	mlx_hook_init(t_rt *rt_dat);

#endif
