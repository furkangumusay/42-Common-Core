/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:19:38 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/09 16:38:43 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int	game_quit(t_data *data)
{
	printf("Exiting game\n");
	ft_exit_mlx(data);
	return (0);
}

void	ft_exit_mlx(t_data *data)
{
	if (data->mlx.mlx_win)
	{
		mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	}
	if (data->map.wall.n_tex.mlx_image)
		mlx_destroy_image(data->mlx.mlx, data->map.wall.n_tex.mlx_image);
	if (data->map.wall.s_tex.mlx_image)
		mlx_destroy_image(data->mlx.mlx, data->map.wall.s_tex.mlx_image);
	if (data->map.wall.w_tex.mlx_image)
		mlx_destroy_image(data->mlx.mlx, data->map.wall.w_tex.mlx_image);
	if (data->map.wall.e_tex.mlx_image)
		mlx_destroy_image(data->mlx.mlx, data->map.wall.e_tex.mlx_image);
	if (data->image.mlx_image)
		mlx_destroy_image(data->mlx.mlx, data->image.mlx_image);
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
	gc_free();
	exit(0);
}
