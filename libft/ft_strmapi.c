/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:28:17 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/23 14:26:42 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = -1;
	str = ft_strdup(s);
	if (!str || !s)
		return (NULL);
	while (s[++i])
		str[i] = f(i, s[i]);
	return (str[i] = '\0', str);
}
