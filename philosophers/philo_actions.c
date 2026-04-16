/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:42:08 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:07:06 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	print_status(philo, "is eating\n");
	ft_usleep(philo->sim->time_to_eat);
	pthread_mutex_lock(&philo->sim->time_mutex);
	philo->meals_eaten++;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->sim->time_mutex);
	release_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping\n");
	ft_usleep(philo->sim->time_to_sleep);
	print_status(philo, "is thinking\n");
	return (0);
}

int	acquire_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks_mutex[philo->left_fork]);
	print_status(philo, "has taken a fork\n");
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->sim->forks_mutex[philo->left_fork]);
		return (1);
	}
	if (philo->sim->philo_count == 1)
	{
		pthread_mutex_unlock(&philo->sim->forks_mutex[philo->left_fork]);
		return (ft_usleep(philo->sim->time_to_die), 1);
	}
	pthread_mutex_lock(&philo->sim->forks_mutex[philo->right_fork]);
	print_status(philo, "has taken a fork\n");
	if (check_death(philo))
		return (release_forks(philo), 1);
	return (0);
}

int	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->sim->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim->forks_mutex[philo->right_fork]);
	return (0);
}
