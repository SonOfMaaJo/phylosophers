/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/25 20:45:23 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_try_eating(t_pĥilosopher *philo, pthread_mutex *first_fork,
		pthread_mutex *second_fork)
{
	long long	start_time;
	char		*status;

	start_time = get_time_in_ms();
	if (pthread_mutex_lock(*first_fork) != 0)
		return (0);
	if (pthread_mutex_lock(*second_fork) != 0
			|| see_dead(philo->rules->is_dead, &philo->rules->dead_lock))
		return (0);
	display("taken a fork", &philo->rules->write_lock, philo->rang);
	philo->last_meal_time = get_time_in_ms();
	if (see_dead(philo->rules->is_dead, &philo->rules->dead_lock))
		return (0);
	display("is eating", &philo->rules->write_lock, philo->rang);
	ft_usleep(philo->rules->time_to_eat);
	if (pthread_mutex_unlock(*first_fork) != 0)
		return (0);
	if (pthread_mutex_unlock(*second_fork) != 0)
		return (0);
	return (1);
}

void	*routine(void *current_philo)
{
	int				should_stop;
	t_philosopher	*philo;
	int				timestamp;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;

	philo = (t_philosopher *)current_philo;
	should_stop = see_dead(philo->rules->is_dead,
			&philo->rules->dead_lock);
	while (should_stop == 0)
	{
		philo_choose_fork(philo, &first_fork, &second_fork);
		if (!philo_try_eating(philo, &first_fork, &second_fork))
			return (NULL);
		display("is sleeping", &philo->rules->write_lock, philo_rang);
		should_stop = see_dead(philo->rules->is_dead,
				&philo->rules->dead_lock);
	}
	return (NULL);
}

t_philosopher	*create_philos(int	numb_philos)
{
	int				i;
	t_philosopher	*philos;

	i = -1;
	philos = (t_philosopher *)malloc(sizeof(t_philosopher * numb_philos));
	if (!philos)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_philos)
	{
		philos[i].status = THINKING;
		philos[i].rang = i + 1;
		philos[i].tid = 0;
	}
	return (philos);
}

t_fork	*create_fork(int	numb_forks)
{
	int		i;
	t_fork	*forks;

	i = -1;
	forks = (t_fork *)malloc(sizeof(t_fork * numb_forks));
	if (!forks)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_forks)
	{
		if (pthread_mutex_init(forks[i]->fork, NULL) != 0)
			return (printf("error : fail to init mutex."),
					ft_free_table((void)forks, i), NULL);
	}
	return (forks);
}
