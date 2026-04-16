/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgumusay <fgumusay@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:57:42 by fgumusay          #+#    #+#             */
/*   Updated: 2024/11/25 13:15:22 by fgumusay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	u_int64_t		last_meal_time;
	int				left_fork;
	int				right_fork;
	pthread_t		thread_id;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_sim
{
	unsigned int	philo_ready;
	unsigned int	philo_count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				meals_required;
	int				is_philo_dead;
	u_int64_t		s_start;
	pthread_mutex_t	general_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	time_mutex;
	t_philo			*philo;
}					t_sim;

int					check_death(t_philo *philo);
void				*monitor_death(void *arg);
void				philo_life(t_philo *ph, t_sim *sim);
int					check_death(t_philo *philo);
int					clean_sim(t_sim *sim);
int					free_mtx(t_sim *sim);
int					init_err(t_sim *sim, int len, int mutex_level);
int					thread_err(t_sim *sim, int len);
void				ft_putstr(const char *str);
void				ft_usleep(u_int64_t time);
u_int64_t			get_time(void);
void				print_status(t_philo *philo, char *status);
int					init_mutexes(t_sim *sim);
int					init_philosophers(t_sim *sim);
int					validate_init(char **argv, t_sim *sim);
int					philo_eat(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					acquire_forks(t_philo *philo);
int					release_forks(t_philo *philo);
int					philo_dead(t_philo *philo);
int					join_threads(t_sim *sim);
int					philo_check(t_philo *philo);
void				*waiting_area(void *arg);

#endif