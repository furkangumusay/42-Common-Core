/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 20:43:49 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/13 17:42:06 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E');
}

static void	set_player_direction2(t_player *player, char c)
{
	if (c == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->fov_x = -0.66;
		player->fov_y = 0;
	}
	else if (c == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->fov_x = 0.66;
		player->fov_y = 0;
	}
}

static void	set_player_direction(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->fov_x = 0;
		player->fov_y = -0.66;
	}
	else if (c == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->fov_x = 0;
		player->fov_y = 0.66;
	}
	else
		set_player_direction2(player, c);
}

void	find_player(char **map, t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				k++;
				if (k > 1)
					safe_exit("Invalid map.");
				data->player.pos_y = i + 0.5;
				data->player.pos_x = j + 0.5;
				set_player_direction(&data->player, map[i][j]);
			}
		}
	}
	if (k < 1)
		safe_exit("Player not found.");
}

void	flood_fill(char **map, int len, int y, int x)
{
	if (x < 0 || y < 0 || y >= len || map[y][x] == '#' || map[y][x] == '\0')
		safe_exit("Invalid map.");
	if (map[y][x] && map[y][x] == '1')
		return ;
	map[y][x] = '1';
	flood_fill(map, len, y + 1, x);
	flood_fill(map, len, y - 1, x);
	flood_fill(map, len, y, x + 1);
	flood_fill(map, len, y, x - 1);
}
