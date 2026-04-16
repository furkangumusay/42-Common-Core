/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:26:29 by fgumusay          #+#    #+#             */
/*   Updated: 2024/06/29 10:45:28 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"
#include "so_long.h"
#include <stdlib.h>

static void	dfs(char **map, int y, int x, char **visited)
{
	if ((visited[y][x + 1] == '0') && (map[y][x + 1] == '0' || map[y][x
			+ 1] == 'C' || map[y][x + 1] == 'E'))
	{
		visited[y][x + 1] = '9';
		dfs(map, y, x + 1, visited);
	}
	if ((visited[y][x - 1] == '0') && (map[y][x - 1] == '0' || map[y][x
			- 1] == 'C' || map[y][x - 1] == 'E'))
	{
		visited[y][x - 1] = '9';
		dfs(map, y, x - 1, visited);
	}
	if ((visited[y + 1][x] == '0') && (map[y + 1][x] == '0' || map[y
			+ 1][x] == 'C' || map[y + 1][x] == 'E'))
	{
		visited[y + 1][x] = '9';
		dfs(map, y + 1, x, visited);
	}
	if ((visited[y - 1][x] == '0') && (map[y - 1][x] == '0' || map[y
			- 1][x] == 'C' || map[y - 1][x] == 'E'))
	{
		visited[y - 1][x] = '9';
		dfs(map, y - 1, x, visited);
	}
}

static void	visited_allocated(char **visited, t_data *data)
{
	if (visited == NULL)
		free_visited(visited, data, 1);
	visited[0] = (char *)malloc(sizeof(char) * data->width);
	if (visited[0] == NULL)
		free_visited(visited, data, 1);
}

static void	check_map(t_data *data, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width - 1)
		{
			if ((data->map[i][j] == 'C' || data->map[i][j] == 'E')
				&& visited[i][j] == '0')
			{
				ft_printf("Error\n");
				free_visited(visited, data, 1);
			}
			j++;
		}
		i++;
	}
	free_visited(visited, data, 0);
}

void	move_control(t_data *data)
{
	char	**visited;
	int		i;
	int		j;

	i = 0;
	visited = (char **)malloc(sizeof(char *) * (data->height + 1));
	visited_allocated(visited, data);
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			visited[i][j] = '0';
			j++;
		}
		i++;
		visited[i] = (char *)malloc(sizeof(char) * data->width);
		if (visited[i] == NULL)
			free_visited(visited, data, 1);
	}
	visited[data->player_x][data->player_y] = '9';
	dfs(data->map, data->player_x, data->player_y, visited);
	check_map(data, visited);
}
