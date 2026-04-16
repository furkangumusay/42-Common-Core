/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:34:50 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/09 16:39:12 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	calculate_ray(t_data *d, t_ray *ray, int x)
{
	double	cam_factor;

	cam_factor = 2 * x / (double)W_WIDTH - 1;
	ray->ray_dir_x = d->player.dir_x + d->player.fov_x * cam_factor;
	ray->ray_dir_y = d->player.dir_y + d->player.fov_y * cam_factor;
	ray->d_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->d_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	init_ray(t_data *d, t_ray *ray)
{
	ray->map_x = (int)d->player.pos_x;
	ray->map_y = (int)d->player.pos_y;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->s_dist_x = (d->player.pos_x - ray->map_x) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->s_dist_x = (ray->map_x + 1.0 - d->player.pos_x) * ray->d_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->s_dist_y = (d->player.pos_y - ray->map_y) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->s_dist_y = (ray->map_y + 1.0 - d->player.pos_y) * ray->d_dist_y;
	}
}

void	trace_ray(t_data *data, t_ray *ray)
{
	while (true)
	{
		if (ray->s_dist_x < ray->s_dist_y)
		{
			ray->s_dist_x += ray->d_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->s_dist_y += ray->d_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.map_2d[ray->map_y][ray->map_x] == '1')
			break ;
	}
}
