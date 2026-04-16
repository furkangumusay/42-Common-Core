/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:54:35 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:18:07 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->check_mutex);
	philo->sim->is_philo_dead = 1;
	pthread_mutex_unlock(&philo->sim->check_mutex);
	printf("%llu	%d	is died\n", get_time() - philo->sim->s_start,
		philo->id + 1);
	return (1);
}

int	join_threads(t_sim *sim)
{
	unsigned int	i;
	int				exit_code;

	exit_code = 0;
	while (1)
	{
		pthread_mutex_lock(&sim->general_mutex);
		if (sim->philo_ready == sim->philo_count)
		{
			pthread_mutex_lock(&sim->time_mutex);
			sim->s_start = get_time();
			pthread_mutex_unlock(&sim->time_mutex);
			pthread_mutex_unlock(&sim->start_mutex);
			pthread_mutex_unlock(&sim->general_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->general_mutex);
	}
	i = -1;
	while (++i < sim->philo_count)
		if (pthread_join(sim->philo[i].thread_id, NULL))
			exit_code = 1;
	return (exit_code);
}

int	philo_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->time_mutex);
	if (philo->last_meal_time == 0)
		philo->last_meal_time = philo->sim->s_start;
	if (philo->sim->time_to_die <= get_time() - philo->last_meal_time)
		return (pthread_mutex_unlock(&philo->sim->time_mutex),
			philo_dead(philo));
	pthread_mutex_unlock(&philo->sim->time_mutex);
	return (0);
}

void	*waiting_area(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim;
	pthread_mutex_lock(&sim->general_mutex);
	sim->philo_ready++;
	pthread_mutex_unlock(&sim->general_mutex);
	pthread_mutex_lock(&sim->start_mutex);
	pthread_mutex_unlock(&sim->start_mutex);
	philo_life(philo, sim);
	return (NULL);
}
