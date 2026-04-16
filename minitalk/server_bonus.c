/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:49:27 by fgumusay          #+#    #+#             */
/*   Updated: 2024/02/25 14:45:46 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	ft_putchar((nbr % 10) + '0');
}

static void	handle_signal(int signal)
{
	static int	bit = 128;
	static int	chr = 0;

	if (signal == SIGUSR1)
		chr += bit;
	bit /= 2;
	if (bit == 0)
	{
		ft_putchar(chr);
		bit = 128;
		chr = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
