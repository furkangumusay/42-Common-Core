/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 11:16:11 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/24 11:44:57 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **arr, size_t i)
{
	while (arr[i])
		free(arr[i++]);
	return (free(arr), NULL);
}

static int	word_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (i);
}

static int	word_lenght(char const *s, char c)
{
	int	len;

	len = 0;
	if (!*s)
		return (0);
	while (*s && *s++ != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		a;
	int		i;

	a = -1;
	i = 0;
	res = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!s || !res)
		return (NULL);
	while (++a < word_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		res[a] = ft_substr(s, i, word_lenght(&s[i], c));
		if (!res[a])
			return (ft_free(res, 0));
		i += word_lenght(&s[i], c);
	}
	return (res[a] = NULL, res);
}
