/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:06:34 by fgumusay          #+#    #+#             */
/*   Updated: 2025/03/25 14:08:48 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr(const char *str)
{
	int	char_count;



	
	char_count = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (*str)
	{
		if (write(1, str, 1) == -1)
			return (-1);
		str++;
		char_count++;
	}
	return (char_count);
}

int	ft_decimaltohex(unsigned int x, char c)
{
	int	char_count;
	int	failure;

	char_count = 0;
	if (x >= 16)
	{
		failure = ft_decimaltohex(x / 16, c);
		if (failure == -1)
			return (-1);
		char_count += failure;
	}
	if (c == 'x')
		failure = write(1, &"0123456789abcdef"[x % 16], 1);
	if (c == 'X')
		failure = write(1, &"0123456789ABCDEF"[x % 16], 1);
	if (failure == -1)
		return (-1);
	return (char_count + 1);
}

int	ft_putnbr(int nbr)
{
	long	x;
	int		char_count;
	int		temp;

	x = nbr;
	char_count = 0;
	if (x < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		x *= -1;
		char_count++;
	}
	if (x > 9)
	{
		temp = ft_putnbr(x / 10);
		if (temp == -1)
			return (-1);
		char_count += temp;
	}
	if (write(1, &"0123456789"[x % 10], 1) == -1)
		return (-1);
	return (char_count + 1);
}

int	ft_putunbr(unsigned int x)
{
	int	char_count;
	int	tmp;

	char_count = 0;
	if (x > 9)
	{
		tmp = ft_putunbr(x / 10);
		if (tmp == -1)
			return (-1);
		char_count += tmp;
	}
	if (write(1, &"0123456789"[x % 10], 1) == -1)
		return (-1);
	return (char_count + 1);
}

int	ft_putpoint(unsigned long x, int flag)
{
	int	char_count;
	int	failure;

	char_count = 0;
	if (flag == 1)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		char_count += 2;
		flag = 0;
	}
	if (x >= 16)
	{
		failure = ft_putpoint(x / 16, 0);
		if (failure == -1)
			return (-1);
		char_count += failure;
	}
	failure = write(1, &"0123456789abcdef"[x % 16], 1);
	if (failure == -1)
		return (-1);
	return (char_count + 1);
}
