/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:27:46 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/28 13:00:46 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	check_size(t_data *data, int i, int j, int flag)
{
	if (data->width == 0)
		data->width = i;
	else if (data->width != i)
		ft_free(data, 1);
	else
		data->width = i;
	if (flag == 1)
		data->height = j + 1;
}

static void	map_create(t_data *data, char *map)
{
	int	i;

	i = 0;
	data->map = (char **)malloc(sizeof(char *) * data->height);
	if (!data->map)
		ft_free(data, 0);
	while (i < (data->height - 1))
	{
		data->map[i] = (char *)malloc(sizeof(char) * (data->width + 1));
		if (!data->map[i])
			ft_free(data, 0);
		i++;
	}
	data->height--;
	fill_data(data, map);
}

void	fill_data(t_data *data, char *map)
{
	char	*tmp;
	int		fd;
	int		i;
	int		j;

	i = -1;
	tmp = (char *)malloc(sizeof(char) * (data->width + 1));
	if (!tmp)
		exit(0);
	fd = open(map, O_RDONLY);
	while (read(fd, tmp, data->width) > 0 && fd > 0 && data->height > ++i)
	{
		j = 0;
		while (data->width > j)
		{
			data->map[i][j] = tmp[j];
			j++;
		}
		data->map[i][j] = '\0';
	}
	data->map[++i] = NULL;
	free(tmp);
	tmp = NULL;
	close(fd);
	map_wall_control(data);
}

void	map_read(t_data *data, int i, int j, char *map)
{
	int		fd;
	char	c;

	fd = open(map, O_RDONLY);
	while (fd > 0 && read(fd, &c, 1) == 1)
	{
		if (c == '0' || c == '1' || c == '\n' || c == 'C' || c == 'E'
			|| c == 'P')
		{
			i++;
			if (c == '\n')
			{
				check_size(data, i, ++j, 1);
				i = 0;
			}
		}
		else
			ft_free(data, 1);
	}
	check_size(data, ++i, ++j, 1);
	close(fd);
	map_create(data, map);
}
