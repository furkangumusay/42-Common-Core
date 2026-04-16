/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:49:52 by fgumusay          #+#    #+#             */
/*   Updated: 2024/02/12 13:08:48 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_update_stash(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = 0;
	if (!stash && buffer)
	{
		new_stash = ft_strdup(buffer);
		if (!new_stash)
			return (NULL);
		return (new_stash);
	}
	new_stash = ft_strjoin(stash, buffer);
	ft_free_stash(&stash, 0);
	return (new_stash);
}

static int	ft_have_nl(char *data_stash)
{
	size_t	i;

	if (!data_stash)
		return (0);
	i = -1;
	while (data_stash[++i] != '\0')
		if (data_stash[i] == '\n')
			return (1);
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*copied_line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] != '\n')
		i++;
	copied_line = malloc(sizeof(char) * (i + 2));
	if (!copied_line)
		return (0);
	j = 0;
	while (j <= i)
	{
		copied_line[j] = stash[j];
		j++;
	}
	return (copied_line[j] = '\0', copied_line);
}

static char	*trim_line(char *stash)
{
	size_t	i;
	char	*trimmed_lines;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (ft_free_stash(&stash, 0));
	trimmed_lines = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!trimmed_lines)
	{
		ft_free_stash(&stash, 0);
		return (NULL);
	}
	ft_free_stash(&stash, 0);
	return (trimmed_lines);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*data_stash [1024];
	char		*current_line;
	long		read_count;

	current_line = 0;
	read_count = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&data_stash[fd], 0));
	while (read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if ((read_count <= 0 && !data_stash[fd]) || read_count == -1)
			return (ft_free_stash(&data_stash[fd], 0));
		buffer[read_count] = '\0';
		data_stash[fd] = ft_update_stash(data_stash[fd], buffer);
		if (ft_have_nl(data_stash[fd]))
		{
			current_line = ft_extract_line(data_stash[fd]);
			if (!current_line)
				return (ft_free_stash(&data_stash[fd], 0));
			return (data_stash[fd] = trim_line(data_stash[fd]), current_line);
		}
	}
	return (ft_free_stash(&data_stash[fd], 1));
}
