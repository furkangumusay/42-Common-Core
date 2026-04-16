/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:21:14 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/28 12:47:00 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "so_long.h"
#include <stdlib.h>

void	setup_data(t_data *data)
{
	data->width = 0;
	data->height = 0;
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->c_count = 0;
	data->p_count = 0;
	data->e_count = 0;
	data->player_img = NULL;
	data->player_exit_img = NULL;
	data->collectible_img = NULL;
	data->wall_img = NULL;
	data->exit_img = NULL;
	data->ground_img = NULL;
	data->img_size = 96;
	data->player_x = 0;
	data->player_y = 0;
	data->move_count = 0;
	data->map = NULL;
}
