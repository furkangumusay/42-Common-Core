/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 12:57:20 by fgumusay          #+#    #+#             */
/*   Updated: 2024/02/25 14:49:55 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result);
}

static void	send_signal(int pid, char c)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(151);
	}
}

static int	check_process_id(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
		return (write(1, "Number of incorrect arguments.\n", 31), 0);
	if (!check_process_id(av[1]))
		return (write(1, "Incorrect process ID\n", 21), 0);
	i = -1;
	pid = ft_atoi(av[1]);
	while (av[2][++i])
		send_signal(pid, av[2][i]);
	send_signal(pid, '\n');
}
