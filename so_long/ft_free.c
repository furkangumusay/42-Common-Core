/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:28:24 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 11:36:57 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "./ft_printf/ft_printf.h"
#include "so_long.h"
#include <stdlib.h>

void	ft_free(t_data *data, int flag)
{
	int	i;

	if (data != NULL)
	{
		if (data->map != NULL)
		{
			i = 0;
			while (i < data->height + 1)
			{
				free(data->map[i]);
				i++;
			}
			free(data->map);
			data->map = NULL;
		}
		free(data);
		data = NULL;
	}
	if (flag == 1)
		ft_printf("Error\n", 2);
	exit(0);
}

int	ft_exit(t_data *data)
{
	if (data->player_img)
		mlx_destroy_image(data->mlx, data->player_img);
	if (data->player_exit_img)
		mlx_destroy_image(data->mlx, data->player_exit_img);
	if (data->collectible_img)
		mlx_destroy_image(data->mlx, data->collectible_img);
	if (data->exit_img)
		mlx_destroy_image(data->mlx, data->exit_img);
	if (data->ground_img)
		mlx_destroy_image(data->mlx, data->ground_img);
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	ft_free(data, 0);
	return (0);
}

void	free_visited(char **visited, t_data *data, int flag)
{
	int	i;

	if (visited != NULL)
	{
		i = 0;
		if (visited[i] != NULL)
		{
			while (i < data -> height + 1)
			{
				free(visited[i]);
				i++;
			}
		}
		free(visited);
		visited = NULL;
	}
	if (flag == 1)
		ft_free(data, 0);
}
