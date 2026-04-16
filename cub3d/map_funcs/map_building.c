/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_building.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:12:26 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/10 15:53:55 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

char	*map_line_build(int len, char *line)
{
	int		i;
	char	*map_line;

	i = -1;
	map_line = gc_malloc(len + 1);
	while (line[++i])
	{
		if (is_valid_char(line[i]))
			map_line[i] = line[i];
		else
			map_line[i] = '#';
	}
	if (i < len)
		while (i < len)
			map_line[i++] = '#';
	map_line[i] = '\0';
	return (map_line);
}

void	build_control_map(t_data *data)
{
	char	**new_map;
	char	**tmp;
	int		i;

	tmp = data->map.map_2d;
	i = data->map.map_height;
	new_map = gc_malloc(sizeof(char *) * (i + 1));
	new_map[i] = NULL;
	i = -1;
	while (tmp[++i])
	{
		new_map[i] = map_line_build(data->map.map_width, tmp[i]);
	}
	find_player(data->map.map_2d, data);
	flood_fill(new_map, data->map.map_height, data->player.pos_y,
		data->player.pos_x);
}

void	build_2d_map(t_data *data, char *mappin)
{
	char	**map2d;
	int		i;
	int		map_width;

	i = 0;
	map_width = 0;
	while (mappin[i] && mappin[i] == '\n')
		i++;
	mappin = &mappin[i];
	i = -1;
	data->map.map_height = get_row_count(mappin);
	map2d = get_map_lines(mappin, 0, 0, data->map.map_height);
	if (!map2d)
		safe_exit("Memory allocation failed");
	data->map.map_2d = map2d;
	while (map2d[++i])
		if (map_width < (int)ft_strlen(map2d[i]))
			map_width = ft_strlen(map2d[i]);
	data->map.map_width = map_width;
	build_control_map(data);
}
