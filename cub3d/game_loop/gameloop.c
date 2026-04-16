/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:05:53 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/06 14:57:36 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx/mlx.h"
#include <math.h>
#include <unistd.h>

static void	move(t_data *d, t_vector direction)
{
	t_vector	new_pos;

	new_pos.x = d->player.pos_x + direction.x * d->player.move_speed;
	new_pos.y = d->player.pos_y + direction.y * d->player.move_speed;
	if (d->map.map_2d[(int)d->player.pos_y][(int)new_pos.x] != '1')
		d->player.pos_x = new_pos.x;
	if (d->map.map_2d[(int)new_pos.y][(int)d->player.pos_x] != '1')
		d->player.pos_y = new_pos.y;
}

static void	handle_player_movement(t_data *d)
{
	if (d->key.w)
		move(d, (t_vector){d->player.dir_x, d->player.dir_y});
	if (d->key.s)
		move(d, (t_vector){-d->player.dir_x, -d->player.dir_y});
	if (d->key.a)
		move(d, (t_vector){-d->player.fov_x, -d->player.fov_y});
	if (d->key.d)
		move(d, (t_vector){d->player.fov_x, d->player.fov_y});
}

static void	rotate_player(t_data *d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->player.dir_x;
	old_plane_x = d->player.fov_x;
	d->player.dir_x = old_dir_x * cos(angle) - d->player.dir_y * sin(angle);
	d->player.dir_y = old_dir_x * sin(angle) + d->player.dir_y * cos(angle);
	d->player.fov_x = old_plane_x * cos(angle) - d->player.fov_y * sin(angle);
	d->player.fov_y = old_plane_x * sin(angle) + d->player.fov_y * cos(angle);
}

static void	turn_player(t_data *d)
{
	if (d->key.right)
		rotate_player(d, d->player.turn_angle);
	if (d->key.left)
		rotate_player(d, -d->player.turn_angle);
}

int	game_loop(t_data *data)
{
	handle_player_movement(data);
	turn_player(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->image.mlx_image, 0, 0);
	return (0);
}
