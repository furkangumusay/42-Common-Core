/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:28:19 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 11:18:52 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "so_long.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int	validate_input(int argc, char *file)
{
	int	fd;
	int	i;

	if (argc != 2)
		return (0);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	while (file[i])
		i++;
	if (file[i - 4] == '.' && file[i - 3] == 'b'
		&& file[i - 2] == 'e' && file[i - 1] == 'r')
		return (1);
	return (0);
}

static void	image_add(t_data *data)
{
	data->player_img = mlx_xpm_file_to_image(data->mlx, "./textures/player.xpm",
			&data->img_size, &data->img_size);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/collectible.xpm",
			&data->img_size, &data->img_size);
	data->wall_img = mlx_xpm_file_to_image(data->mlx, "./textures/wall.xpm",
			&data->img_size, &data->img_size);
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "./textures/exit.xpm",
			&data->img_size, &data->img_size);
	data->ground_img = mlx_xpm_file_to_image(data->mlx, "./textures/ground.xpm",
			&data->img_size, &data->img_size);
	data->player_exit_img = mlx_xpm_file_to_image(data->mlx,
			"./textures/player_exit.xpm",
			&data->img_size, &data->img_size);
	if (data->player_img == NULL || data->collectible_img == NULL
		|| data->wall_img == NULL || data->exit_img == NULL
		|| data->ground_img == NULL || data->player_exit_img == NULL)
		ft_exit(data);
}

static void	add_graphic_2(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'C')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->collectible_img,
			j * 96, i * 96);
	else if (data->map[i][j] == 'E')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->exit_img, j
			* 96, i * 96);
	else if (data->map[i][j] == 'P')
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->player_img, j
			* 96, i * 96);
}

void	add_graphics(t_data *data, int i, int j)
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
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!validate_input(argc, argv[1]))
		ft_free(NULL, 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_free(data, 0);
	setup_data(data);
	map_read(data, 0, 0, argv[1]);
	mlx_control(data);
	image_add(data);
	add_graphics(data, -1, -1);
	mlx_hook(data->mlx_win, 2, 0, ft_move, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
	mlx_loop(data->mlx);
	ft_exit(data);
}
