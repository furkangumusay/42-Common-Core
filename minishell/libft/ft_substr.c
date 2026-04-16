/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:17:29 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/20 16:39:27 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		new[j] = '\0';
		return (new);
	}
	return (NULL);
}
