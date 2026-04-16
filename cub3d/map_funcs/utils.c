/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 06:20:53 by ndogan            #+#    #+#             */
/*   Updated: 2025/01/08 03:51:52 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdbool.h>
#include <unistd.h>

bool	is_white_space(char c)
{
	if (c && (c == 32 || (c <= 13 && c >= 7)))
		return (true);
	return (false);
}

int	get_space_count(char *str, int location, char s_or_e)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s_or_e == 's')
	{
		while (str[location + i] && is_white_space(str[location + i]))
		{
			count++;
			i++;
		}
	}
	else
	{
		while (str[location + i] && is_white_space(str[location + i]))
		{
			count++;
			i--;
		}
	}
	return (count);
}

int	get_file_size(int fd)
{
	size_t	file_len;
	char	buf;
	int		read_bit;

	read_bit = 1;
	file_len = 0;
	while (read_bit > 0)
	{
		read_bit = read(fd, &buf, 1);
		if (read_bit == -1)
			safe_exit("Read failed!");
		file_len++;
	}
	close(fd);
	return (file_len);
}
