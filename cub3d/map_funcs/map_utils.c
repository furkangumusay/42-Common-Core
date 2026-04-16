/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:18:42 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/09 16:50:17 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	get_row_count(char *mappin)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (mappin[i])
	{
		if (mappin[i] == '\n')
			rows++;
		i++;
	}
	rows++;
	return (rows);
}

char	**get_map_lines(char *mappin, int row_index, int start,
		int row_count)
{
	int		len;
	char	**map2d;
	int		i;

	i = -1;
	map2d = (char **)gc_malloc((row_count + 1) * sizeof(char *));
	add_garbage_c(map2d);
	while (mappin[++i])
	{
		if (mappin[i] == '\n' || mappin[i + 1] == '\0')
		{
			if (mappin[i + 1] == '\0')
				len = (i - start + 1);
			else
				len = (i - start);
			map2d[row_index] = (char *)gc_malloc((len + 1) * sizeof(char));
			add_garbage_c(map2d[row_index]);
			if (!map2d[row_index])
				safe_exit("Memory allocation failed");
			ft_strlcpy(map2d[row_index], &mappin[start], len + 1);
			map2d[row_index++][len] = '\0';
			start = i + 1;
		}
	}
	return (map2d[row_index] = NULL, map2d);
}
