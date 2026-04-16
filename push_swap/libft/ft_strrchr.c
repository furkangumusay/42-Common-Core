/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:26:49 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/21 12:32:01 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) + 1;
	while (--i >= 0)
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (0);
}
