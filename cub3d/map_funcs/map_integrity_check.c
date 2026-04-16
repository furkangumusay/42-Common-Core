/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_integrity_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:59:14 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/13 20:21:44 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

static void	check_map_integrity(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]) && !is_white_space(map[i][j]))
				safe_exit("Invalid map: Invalid character detected.");
			j++;
		}
		i++;
	}
}

void	map_check(t_data *data)
{
	t_map	*tmp_map;

	tmp_map = &data->map;
	check_map_integrity(tmp_map->map_2d);
}
