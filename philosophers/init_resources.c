/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:03:53 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:04:59 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_mutexes(t_sim *sim)
{
	unsigned int	i;

	i = -1;
	sim->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->philo_count);
	if (!sim->forks_mutex)
		return (1);
	while (++i < sim->philo_count)
		if (pthread_mutex_init(&sim->forks_mutex[i], NULL))
			return (init_err(sim, i, 0));
	if (pthread_mutex_init(&sim->general_mutex, NULL))
		init_err(sim, i, 0);
	if (pthread_mutex_init(&sim->check_mutex, NULL))
		init_err(sim, i, 1);
	if (pthread_mutex_init(&sim->time_mutex, NULL))
		init_err(sim, i, 2);
	if (pthread_mutex_init(&sim->start_mutex, NULL))
		init_err(sim, i, 3);
	return (0);
}

int	init_philosophers(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	sim->philo = (t_philo *)malloc(sizeof(t_philo) * sim->philo_count);
	if (!sim->philo)
		return (1);
	while (i < sim->philo_count)
	{
		sim->philo[i].sim = sim;
		sim->philo[i].id = i;
		sim->philo[i].meals_eaten = 0;
		sim->philo[i].last_meal_time = 0;
		sim->philo[i].left_fork = i;
		sim->philo[i].right_fork = (i + 1) % sim->philo_count;
		i++;
	}
	return (0);
}
