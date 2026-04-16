/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:07:23 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/10 14:38:33 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx/mlx.h"
#include <unistd.h>

void	init_data(t_data *data)
{
	data->map = (t_map){0};
	data->map.floor_color = (t_color){-1, -1, -1, 0, false};
	data->map.ceiling_color = (t_color){-1, -1, -1, 0, false};
	data->map.wall = (t_wall){0};
	data->image = (t_image){0};
	data->player = (t_player){0};
	data->key = (t_keys){0};
}

static void	set_rgb_color(t_color *color)
{
	color->rgb_value = (color->r << 16 | color->g << 8 | color->b);
	color->is_defined = true;
}

void	init_graphics(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		safe_exit("Mlx initialization problems!");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, W_WIDTH, W_HEIGHT,
			"cub3d");
	if (!data->mlx.mlx_win)
		ft_exit_mlx(data);
	data->player.move_speed = 0.08;
	data->player.turn_angle = 0.05;
	data->image.mlx_image = mlx_new_image(data->mlx.mlx, W_WIDTH, W_HEIGHT);
	if (!data->image.mlx_image)
		ft_exit_mlx(data);
	data->image.pixel_data = (int *)mlx_get_data_addr(data->image.mlx_image,
			&data->image.bits_per_pixel, &data->image.line_length,
			&data->image.endian);
	if (!data->image.pixel_data)
		ft_exit_mlx(data);
	set_rgb_color(&data->map.ceiling_color);
	set_rgb_color(&data->map.floor_color);
}

static void	set_texture(t_data *d, t_image *image, char *path)
{
	image->mlx_image = mlx_xpm_file_to_image(d->mlx.mlx, path, &image->width,
			&image->height);
	if (!image->mlx_image)
		ft_exit_mlx(d);
	image->pixel_data = (int *)mlx_get_data_addr(image->mlx_image,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	if (!image->pixel_data)
		ft_exit_mlx(d);
}

void	init_texture(t_data *d)
{
	if (d->map.wall.n_tex.image_path)
		set_texture(d, &(d->map.wall.n_tex), d->map.wall.n_tex.image_path);
	if (d->map.wall.s_tex.image_path)
		set_texture(d, &(d->map.wall.s_tex), d->map.wall.s_tex.image_path);
	if (d->map.wall.w_tex.image_path)
		set_texture(d, &(d->map.wall.w_tex), d->map.wall.w_tex.image_path);
	if (d->map.wall.e_tex.image_path)
		set_texture(d, &(d->map.wall.e_tex), d->map.wall.e_tex.image_path);
}
