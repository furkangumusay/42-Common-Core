/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:21:17 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:03:35 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

int	clean_sim(t_sim *sim)
{
	int	exit_code;

	exit_code = 0;
	if (free_mtx(sim))
		exit_code = 1;
	if (sim->philo)
		free(sim->philo);
	return (exit_code);
}

int	free_mtx(t_sim *sim)
{
	unsigned int	i;
	int				exit_code;

	i = -1;
	exit_code = 0;
	while (++i < sim->philo_count)
		if (pthread_mutex_destroy(&sim->forks_mutex[i]))
			exit_code = 1;
	if (pthread_mutex_destroy(&sim->check_mutex))
		exit_code = 1;
	if (pthread_mutex_destroy(&sim->time_mutex))
		exit_code = 1;
	if (pthread_mutex_destroy(&sim->start_mutex))
		exit_code = 1;
	if (pthread_mutex_destroy(&sim->general_mutex))
		exit_code = 1;
	if (sim->forks_mutex)
		free(sim->forks_mutex);
	return (exit_code);
}

int	init_err(t_sim *sim, int len, int mutex_level)
{
	while (--len >= 0)
		pthread_mutex_destroy(&sim->forks_mutex[len]);
	if (sim->forks_mutex)
		free(sim->forks_mutex);
	if (mutex_level > 0)
		pthread_mutex_destroy(&sim->general_mutex);
	if (mutex_level > 1)
		pthread_mutex_destroy(&sim->check_mutex);
	if (mutex_level > 2)
		pthread_mutex_destroy(&sim->time_mutex);
	return (1);
}

int	thread_err(t_sim *sim, int len)
{
	pthread_mutex_unlock(&sim->start_mutex);
	while (--len >= 0)
		pthread_join(sim->philo[len].thread_id, NULL);
	clean_sim(sim);
	return (1);
}

void	ft_putstr(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
}
