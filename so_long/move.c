/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:28:52 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 10:33:05 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include "./minilibx/mlx.h"
#include "so_long.h"

static void	add_graphic_2(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'C')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->collectible_img,
			j * 96, i * 96);
	else if (data->map[i][j] == 'E')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->player_exit_img,
			j * 96, i * 96);
}

static int	add_graphics_exit(t_data *data, int i, int j)
{
	while (++i < data->height)
	{
		while (++j < data->width - 1)
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->wall_img, j * 96, i * 96);
			else if (data->map[i][j] == '0')
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->ground_img, j * 96, i * 96);
			add_graphic_2(data, i, j);
		}
		j = -1;
	}
	return (0);
}

static int	can_move_2(t_data *data, int x, int y)
{
	ft_printf("Step: %d\n", ++data->move_count);
	data->map[data->player_x][data->player_y] = '0';
	data->map[x][y] = 'E';
	data->player_x = x;
	data->player_y = y;
	add_graphics_exit(data, -1, -1);
	return (0);
}

static int	can_move(t_data *data, int x, int y)
{
	if (data->map[data -> player_x][data -> player_y] == 'E'
		&& data -> map[x][y] == '1')
		return (add_graphics_exit(data, -1, -1));
	else if (data->map[x][y] == 'E' && data->c_count != 0)
		return (can_move_2(data, x, y));
	else if (data->map[x][y] == 'E' && data->c_count == 0)
	{
		ft_printf("Step: %d\n", ++data->move_count);
		ft_exit(data);
	}
	else if (data->map[x][y] != '1')
	{
		ft_printf("Step: %d\n", ++data->move_count);
		if (data->map[x][y] == 'C')
			data->c_count--;
		if (data->map[data->player_x][data->player_y] != 'E')
			data->map[data->player_x][data->player_y] = '0';
		data->map[x][y] = 'P';
		data->player_x = x;
		data->player_y = y;
	}
	add_graphics(data, -1, -1);
	return (0);
}

int	ft_move(int key_code, t_data *data)
{
	int	x;
	int	y;

	y = data->player_x;
	x = data->player_y;
	if (key_code == W)
		y--;
	else if (key_code == S)
		y++;
	else if (key_code == A)
		x--;
	else if (key_code == D)
		x++;
	else if (key_code == ESC)
		ft_exit(data);
	else
		return (0);
	mlx_clear_window(data->mlx, data->mlx_win);
	can_move(data, y, x);
	return (0);
}
