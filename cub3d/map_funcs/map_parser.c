/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:39:11 by ndogan            #+#    #+#             */
/*   Updated: 2025/01/09 16:38:17 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

const char	*parse_number(const char *str, int *s)
{
	int	flag;

	flag = 0;
	while (*str != '\0' && *str != '\n' && *str != ',')
	{
		while (*str >= '0' && *str <= '9')
		{
			*s = *s * 10 + (*str - '0');
			if (*s == 0 && *(str + 1) == '0')
				safe_exit("Invalid RGB value!");
			flag = 1;
			str++;
		}
		while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v'
			|| *str == '\f')
		{
			str++;
			if (*str >= '0' && *str <= '9' && flag == 1)
				safe_exit("Invalid RGB value!");
		}
		if (!ft_isdigit(*str) && !is_white_space(*str) && !(*str == ','))
			safe_exit("Invalid RGB value!");
	}
	return (str);
}

int	parse_rgb_values(const char *str, int *data)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (*str && i < 3)
	{
		s = 0;
		if (!(*str >= '0' && *str <= '9') && !(*str == ' ' || *str == '\t'
				|| *str == '\r' || *str == '\v' || *str == '\f'))
			return (1);
		str = parse_number(str, &s);
		data[i++] = s;
		if (*str != '\0' && *str == ',')
			str++;
	}
	return (0);
}

void	parse_single_param(char *mappin, t_map *map, int *i, int *c)
{
	if (ft_strncmp(&mappin[*i], "NO", 2) == 0)
		*i += get_path(&mappin[*i] + 2, &map->wall.n_tex.image_path);
	else if (ft_strncmp(&mappin[*i], "SO", 2) == 0)
		*i += get_path(&mappin[*i] + 2, &map->wall.s_tex.image_path);
	else if (ft_strncmp(&mappin[*i], "WE", 2) == 0)
		*i += get_path(&mappin[*i] + 2, &map->wall.w_tex.image_path);
	else if (ft_strncmp(&mappin[*i], "EA", 2) == 0)
		*i += get_path(&mappin[*i] + 2, &map->wall.e_tex.image_path);
	else if (mappin[*i] == 'F')
		*i += parse_rgb(&mappin[*i], &map->floor_color);
	else if (mappin[*i] == 'C')
		*i += parse_rgb(&mappin[*i], &map->ceiling_color);
	else
		safe_exit("Invalid value in map!");
	(*c)++;
}

void	parse_map_params(char *mappin, t_map *map, int *i)
{
	int	c;

	c = 0;
	while (mappin[++(*i)])
	{
		if (c == 6)
		{
			everything_okay(*map);
			break ;
		}
		if (is_white_space(mappin[*i]))
			continue ;
		parse_single_param(mappin, map, i, &c);
	}
}

void	parse_map(char *mappin, t_data *data)
{
	int	i;

	i = -1;
	parse_map_params(mappin, &(data->map), &i);
	build_2d_map(data, &mappin[i]);
}
