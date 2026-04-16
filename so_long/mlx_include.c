/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_include.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:28:41 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 11:47:43 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "so_long.h"
#include <stdlib.h>

void	mlx_control(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		ft_free(data, 0);
	data->mlx_win = mlx_new_window(data->mlx, (data->width - 1) * 96,
			data->height * 96, "so_long");
	if (data->mlx_win == NULL)
		ft_free(data, 0);
}
