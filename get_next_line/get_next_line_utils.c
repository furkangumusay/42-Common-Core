/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:49:28 by fgumusay          #+#    #+#             */
/*   Updated: 2024/02/12 13:14:22 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = -1;
	while (str[++len])
		;
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*s;
	int		i;

	i = -1;
	s = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (0);
	while (str[++i] != '\0')
		s[i] = str[i];
	return (s[i] = '\0', s);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	strlen1;
	size_t	strlen2;
	size_t	i;
	char	*new_str;

	if (!str1 || !str2)
		return (NULL);
	strlen1 = ft_strlen(str1);
	strlen2 = ft_strlen(str2) + 1;
	new_str = (char *)malloc(strlen1 + strlen2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*str1)
		new_str[i++] = *str1++;
	while (*str2)
		new_str[i++] = *str2++;
	return (new_str[i] = '\0', new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s)
	{
		if (start >= ft_strlen(s) || len == 0)
			return (ft_strdup(""));
		i = 0;
		while (i < len && s[i + start])
			i++;
		new = (char *)malloc(i + 1);
		if (!new)
			return (NULL);
		j = 0;
		while (j < i)
		{
			new[j] = s[start + j];
			j++;
		}
		return (new[j] = '\0', new);
	}
	return (NULL);
}

void	*ft_free_stash(char **stash, int create_line)
{
	char	*line;

	if (!*stash)
		return (NULL);
	if (!create_line)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	else if (create_line)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
}
