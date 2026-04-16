/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 17:10:25 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/09 16:39:19 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_wall_bounds(t_ray *ray)
{
	ray->line_h = (int)(W_HEIGHT / ray->p_wall_dist);
	ray->draw_start = -ray->line_h / 2 + W_HEIGHT / 2;
	if (ray->draw_start < 0 || ray->draw_start >= W_HEIGHT)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + W_HEIGHT / 2;
	if (ray->draw_end >= W_HEIGHT || ray->draw_end < 0)
		ray->draw_end = W_HEIGHT - 1;
}

void	select_wall_texture(t_data *d, t_ray *ray)
{
	if (ray->ray_dir_x < 0 && ray->side == 0)
	{
		ray->active_tex.width = d->map.wall.w_tex.width;
		ray->active_tex.height = d->map.wall.w_tex.height;
	}
	else if (ray->ray_dir_x >= 0 && ray->side == 0)
	{
		ray->active_tex.width = d->map.wall.e_tex.width;
		ray->active_tex.height = d->map.wall.e_tex.height;
	}
	if (ray->ray_dir_y < 0 && ray->side != 0)
	{
		ray->active_tex.width = d->map.wall.n_tex.width;
		ray->active_tex.height = d->map.wall.n_tex.height;
	}
	else if (ray->ray_dir_y >= 0 && ray->side != 0)
	{
		ray->active_tex.width = d->map.wall.s_tex.width;
		ray->active_tex.height = d->map.wall.s_tex.height;
	}
}
