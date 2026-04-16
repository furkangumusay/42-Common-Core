/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:56:41 by fgumusay          #+#    #+#             */
/*   Updated: 2023/12/22 17:26:54 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n && ++i)
		n = n / 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	long	x;

	x = n;
	len = nlen(x);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (x < 0)
		s[0] = '-';
	x *= !(x < 0) - (x < 0);
	if (!x)
		s[0] = '0';
	s[len] = '\0';
	while (x > 0)
	{
		s[--len] = (x % 10) + '0';
		x /= 10;
	}
	return (s);
}
