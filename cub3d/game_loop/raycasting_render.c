/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:22:12 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/10 16:21:10 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	calc_texture_coords(t_data *d, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = d->player.pos_y + ray->p_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = d->player.pos_x + ray->p_wall_dist * ray->ray_dir_x;
	ray->wall_x -= (int)ray->wall_x;
	ray->tex.x_coord = (int)(ray->wall_x * (double)ray->active_tex.width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex.x_coord = ray->active_tex.width - ray->tex.x_coord - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex.x_coord = ray->active_tex.width - ray->tex.x_coord - 1;
	ray->step = (double)ray->active_tex.height / ray->line_h;
	ray->tex.offset = (ray->draw_start - W_HEIGHT / 2 + ray->line_h / 2)
		* ray->step;
}	

static void	render_wall_texture(t_data *d, int x, t_ray *ray, int y)
{
	if (ray->side == 1 && ray->ray_dir_y < 0)
		d->image.pixel_data[y * W_WIDTH
			+ x] = d->map.wall.n_tex.pixel_data[d->map.wall.n_tex.width
			* ray->tex.y_coord + ray->tex.x_coord];
	else if (ray->side == 1 && ray->ray_dir_y >= 0)
		d->image.pixel_data[y * W_WIDTH
			+ x] = d->map.wall.s_tex.pixel_data[d->map.wall.s_tex.width
			* ray->tex.y_coord + ray->tex.x_coord];
	if (ray->side == 0 && ray->ray_dir_x < 0)
		d->image.pixel_data[y * W_WIDTH
			+ x] = d->map.wall.w_tex.pixel_data[d->map.wall.w_tex.width
			* ray->tex.y_coord + ray->tex.x_coord];
	else if (ray->side == 0 && ray->ray_dir_x >= 0)
		d->image.pixel_data[y * W_WIDTH
			+ x] = d->map.wall.e_tex.pixel_data[d->map.wall.e_tex.width
			* ray->tex.y_coord + ray->tex.x_coord];
	ray->tex.offset += ray->step;
}

static void	render_column(t_data *d, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < W_HEIGHT)
	{
		ray->tex.y_coord = (int)ray->tex.offset;
		if (y < ray->draw_start)
			d->image.pixel_data[y * W_WIDTH
				+ x] = d->map.ceiling_color.rgb_value;
		else if (y > ray->draw_end)
			d->image.pixel_data[y * W_WIDTH + x] = d->map.floor_color.rgb_value;
		else
			render_wall_texture(d, x, ray, y);
		y++;
	}
}

static void	calc_perp_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->p_wall_dist = ray->s_dist_x - ray->d_dist_x;
	else
		ray->p_wall_dist = ray->s_dist_y - ray->d_dist_y;
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < W_WIDTH)
	{
		calculate_ray(data, &ray, x);
		init_ray(data, &ray);
		trace_ray(data, &ray);
		select_wall_texture(data, &ray);
		calc_perp_wall_dist(&ray);
		calc_wall_bounds(&ray);
		calc_texture_coords(data, &ray);
		render_column(data, x, &ray);
	}
}
