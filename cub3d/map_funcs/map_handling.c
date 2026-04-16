/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:59:35 by fgumusay          #+#    #+#             */
/*   Updated: 2025/01/10 15:59:36 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

int	map_file_ctrl(char *file_name)
{
	int	i;
	int	file_size;

	i = ft_strlen(file_name);
	if (file_name[i - 1] != 'b' || file_name[i - 2] != 'u' || file_name[i
			- 3] != 'c' || file_name[i - 4] != '.')
	{
		safe_exit("The map extension is invalid!");
	}
	i = open(file_name, O_RDWR);
	if (i == -1)
		safe_exit("Map file could not be opened!");
	file_size = get_file_size(i);
	if (file_size >= 20000)
		safe_exit("Map is too big");
	close(i);
	return (file_size);
}

char	*read_map(char *file_name, int file_size, int fd)
{
	char	*map;
	char	*temp_map;
	int		start_space_count;
	int		end_space_count;
	int		map_size;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		safe_exit("Map file could not be opened!");
	temp_map = gc_malloc(file_size + 1);
	if (read(fd, temp_map, file_size) == -1)
		safe_exit("Read failed");
	close(fd);
	temp_map[file_size] = 0;
	start_space_count = get_space_count(temp_map, 0, 's');
	end_space_count = get_space_count(temp_map, file_size - 2, 'e');
	map_size = file_size - (start_space_count + end_space_count);
	map = gc_malloc(map_size);
	ft_strlcpy(map, temp_map + start_space_count, map_size);
	add_garbage_c(map);
	safe_free(temp_map);
	return (map);
}
