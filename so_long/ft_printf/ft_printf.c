/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:59:15 by fgumusay          #+#    #+#             */
/*   Updated: 2024/05/25 13:16:51 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_format(va_list *args, char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg((*args), int)));
	else if (c == 's')
		return (ft_putstr(va_arg((*args), const char *)));
	else if (c == 'p')
		return (ft_putpoint(va_arg((*args), unsigned long), 1));
	else if (c == 'x' || c == 'X')
		return (ft_decimaltohex(va_arg((*args), unsigned int), c));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg((*args), int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg((*args), unsigned int)));
	else
		return (ft_putchar('%'));
}

static int	ft_flag_check(const char *str, int i)
{
	return (str[i] == '%' && (str[i + 1] == 'c' || str[i + 1] == 's'
			|| str[i + 1] == 'p' || str[i + 1] == 'd'
			|| str[i + 1] == 'i' || str[i + 1] == 'u'
			|| str[i + 1] == 'x' || str[i + 1] == 'X' || str[i + 1] == '%'));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		char_count;
	int		tmp;

	i = -1;
	tmp = 0;
	char_count = 0;
	va_start(args, str);
	while (str[++i])
	{
		if (ft_flag_check(str, i))
			tmp = ft_format(&args, str[++i]);
		else if (str[i] != '%')
			tmp = ft_putchar(str[i]);
		if (tmp == -1)
		{
			va_end(args);
			return (-1);
		}
		char_count += tmp;
	}
	va_end(args);
	return (char_count);
}
