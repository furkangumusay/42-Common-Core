/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:10:51 by ndogan            #+#    #+#             */
/*   Updated: 2025/03/25 14:10:02 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "cub3d.h"
#include <unistd.h>

static int	handle_key_input(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_ESC)
		game_quit(data);
	if (keycode == KEY_W)
		data->key.w = true;
	if (keycode == KEY_A)
		data->key.a = true;
	if (keycode == KEY_S)
		data->key.s = true;
	if (keycode == KEY_D)
		data->key.d = true;
	if (keycode == KEY_LEFT)
		data->key.left = true;
	if (keycode == KEY_RIGHT)
		data->key.right = true;
	return (0);
}

static int	handle_key_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_W)
		data->key.w = false;
	if (keycode == KEY_A)
		data->key.a = false;
	if (keycode == KEY_S)
		data->key.s = false;
	if (keycode == KEY_D)
		data->key.d = false;
	if (keycode == KEY_LEFT)
		data->key.left = false;
	if (keycode == KEY_RIGHT)
		data->key.right = false;
	return (0);
}

static void	initial_and_checks(char *file_name, t_data *data)
{
	int		file_size;
	char	*map;

	file_size = map_file_ctrl(file_name);
	map = read_map(file_name, file_size, 0);
	init_data(data);
	parse_map(map, data);
	map_check(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		initial_and_checks(argv[1], &data);
		init_graphics(&data);
		init_texture(&data);
		mlx_do_key_autorepeatoff(data.mlx.mlx);
		mlx_hook(data.mlx.mlx_win, 2, 1L, handle_key_input, &data);
		mlx_hook(data.mlx.mlx_win, 3, 2L, handle_key_release, &data);
		mlx_loop_hook(data.mlx.mlx, game_loop, &data);
		mlx_hook(data.mlx.mlx_win, 17, 1L << 17, game_quit, &data);
		mlx_loop(data.mlx.mlx);
	}
	else
		write(1, "Error: Missing or extra arguments!", 34);
	return (0);
}
