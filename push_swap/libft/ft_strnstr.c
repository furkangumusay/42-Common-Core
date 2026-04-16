/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:29:09 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/22 14:40:15 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = -1;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[++h] && h < len)
	{
		n = 0;
		while (haystack[h + n] == needle[n] && haystack[h + n]
			&& h + n < len)
			n++;
		if (!needle[n])
			return ((char *)(haystack + h));
	}
	return (0);
}
