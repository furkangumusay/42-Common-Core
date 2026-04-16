/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:21:35 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/09 21:48:15 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;

	i = -1;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (!dstsize || dstsize <= d)
		return (dstsize + s);
	while (src[++i] && i < dstsize - d - 1)
		dst[d + i] = src[i];
	return (dst[d + i] = '\0', d + s);
}
