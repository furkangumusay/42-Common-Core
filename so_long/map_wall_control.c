/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:26:56 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/28 12:52:17 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_arg_control(t_data *data, int i, int j)
{
	while (i < data->height)
	{
		while (j < data->width - 1)
		{
			if (data->map[i][j] == 'C')
				data->c_count++;
			else if (data->map[i][j] == 'E')
				data->e_count++;
			else if (data->map[i][j] == 'P')
			{
				data->player_x = i;
				data->player_y = j;
				data->p_count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (data->c_count < 1 || data->e_count != 1 || data->p_count != 1)
		ft_free(data, 1);
	move_control(data);
}

void	map_wall_control(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->height)
	{
		i = 0;
		while (i < data->width - 1)
		{
			if (data->map[0][i] != '1' || data->map[j][0] != '1')
				ft_free(data, 1);
			if (data->map[data->height - 1][i] != '1'
				|| data->map[j][data->width - 2] != '1')
				ft_free(data, 1);
			i++;
		}
		j++;
	}
	map_arg_control(data, 0, 0);
}
