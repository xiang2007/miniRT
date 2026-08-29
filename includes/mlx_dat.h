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

void	handle_key_z(t_rt *win);
void	handle_camera_move(int key, t_rt *win);
void	handle_move_object(int key, t_rt *win);

void	rebuild_world_bvh(t_world *world);

void	handle_rotate_object(int key, t_rt *win);
void	handle_camera_rotate(int key, t_rt *win);

int		mouse_select(int button, int x, int y, t_rt *win);

void	draw_controls(t_rt *rt);
void	mlx_swap_buffers(t_mlx *m);

void	rotate_axis_key(int key, t_vec3 *axis, double *angle);

#endif
