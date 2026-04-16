/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:04:24 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/22 14:20:19 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	s[i] = '\0';
	return (s);
}
