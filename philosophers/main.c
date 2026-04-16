/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:18:12 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:05:39 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->check_mutex);
	pthread_mutex_lock(&philo->sim->general_mutex);
	if (philo->sim->philo_ready == 0)
		philo->sim->is_philo_dead = 1;
	pthread_mutex_unlock(&philo->sim->general_mutex);
	if (philo->sim->is_philo_dead)
	{
		pthread_mutex_unlock(&philo->sim->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->check_mutex);
	return (0);
}

void	philo_life(t_philo *ph, t_sim *sim)
{
	if (!(ph->id % 2))
		ft_usleep(sim->time_to_eat / 2);
	while (1)
	{
		if (acquire_forks(ph))
			break ;
		philo_eat(ph);
		philo_sleep(ph);
		if (check_death(ph))
			break ;
		if (sim->meals_required != -1 && ph->meals_eaten == sim->meals_required)
		{
			pthread_mutex_lock(&sim->check_mutex);
			sim->philo_ready--;
			pthread_mutex_unlock(&sim->check_mutex);
		}
	}
}

void	*monitor_death(void *arg)
{
	unsigned int	i;
	t_sim			*sim;

	sim = arg;
	pthread_mutex_lock(&sim->start_mutex);
	pthread_mutex_unlock(&sim->start_mutex);
	while (1)
	{
		i = -1;
		while (++i < sim->philo_count)
		{
			if (check_death(&sim->philo[i]))
				break ;
			if (philo_check(&sim->philo[i]))
				break ;
		}
		if (i != sim->philo_count)
			break ;
	}
	return (NULL);
}

int	begin_sim(t_sim *sim)
{
	unsigned int	i;
	pthread_t		thread;

	i = -1;
	pthread_mutex_lock(&sim->start_mutex);
	if (pthread_create(&thread, NULL, monitor_death, sim))
		return (1);
	else
		while (++i < sim->philo_count)
			if (pthread_create(&sim->philo[i].thread_id, NULL, waiting_area,
					&sim->philo[i]))
				return (thread_err(sim, i));
	if (join_threads(sim))
		return (pthread_join(thread, NULL) || 1);
	if (pthread_join(thread, NULL))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 5 && argc != 6)
		return (ft_putstr("Invalid number of arguments.\n"), 1);
	if (validate_init(argv, &sim))
		return (ft_putstr("Initialization failed.\n"), 1);
	if (begin_sim(&sim))
		return (clean_sim(&sim), ft_putstr("Simulation failed.\n"), 1);
	clean_sim(&sim);
	return (0);
}
