/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:59:22 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/10 15:59:25 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] <= 13 && str[i] >= 7)))
		i++;
	return (i);
}

int	everything_okay(t_map map)
{
	if (!map.wall.n_tex.image_path)
		safe_exit("Missing north texture!");
	if (!map.wall.s_tex.image_path)
		safe_exit("Missing south texture!");
	if (!map.wall.w_tex.image_path)
		safe_exit("Missing west texture!");
	if (!map.wall.e_tex.image_path)
		safe_exit("Missing east texture!");
	if (map.floor_color.r < 0 || map.floor_color.g < 0 || map.floor_color.b < 0)
		safe_exit("Missing or invalid floor color!");
	if (map.ceiling_color.r < 0 || map.ceiling_color.g < 0
		|| map.ceiling_color.b < 0)
		safe_exit("Missing or invalid ceiling color!");
	return (1);
}

int	get_path(char *map, char **path)
{
	int	i;
	int	s_len;
	int	len;

	i = 0;
	len = 0;
	if (*path)
		safe_exit("Repeating texture values detected!");
	while (map[i] && is_white_space(map[i]))
		i++;
	s_len = i;
	while (map[i] && !is_white_space(map[i]))
	{
		i++;
		len++;
	}
	*path = gc_malloc(len + 1);
	ft_strlcpy(*path, map + s_len, len + 1);
	i = open(*path, O_RDONLY);
	if (i == -1)
		safe_exit("Invalide path!");
	close(i);
	return (s_len + len + 2);
}

int	parse_rgb(const char *str, t_color *color)
{
	int	i;
	int	count;
	int	data[3];

	i = 0;
	count = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ',' && str[i + 1] == ',')
			safe_exit("Invalid RGB value!");
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		safe_exit("Invalid RGB value!");
	if (parse_rgb_values(str + 1 + ft_isspace(str + 1), data))
		safe_exit("Invalid RGB value!");
	if (data[0] < 0 || data[0] > 255 || data[1] < 0 || data[1] > 255
		|| data[2] < 0 || data[2] > 255)
		safe_exit("Invalid RGB value!");
	color->r = data[0];
	color->g = data[1];
	color->b = data[2];
	return (i);
}
