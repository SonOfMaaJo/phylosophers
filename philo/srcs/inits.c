/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/18 16:33:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_mutex(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->nb_eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->meal_lock);
		return (0);
	}
	return (1);
}

static void	*routine(void *current_philo)
{
	t_philosopher	*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				start;

	philo = (t_philosopher *)current_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->start_lock);
		start = philo->rules->start;
		pthread_mutex_unlock(&philo->rules->start_lock);
		usleep(WAIT_TO_START);
		if (start)
			break ;
	}
	usleep(WAIT_TO_START);
	if (philo->rang % 2 == 1 && philo->rules->nb_philos > 1)
		ft_usleep(WAIT_TO_HOLD);
	get_fork(philo, &first_fork, &second_fork);
	philo_loop(philo, first_fork, second_fork);
	return (NULL);
}

t_philosopher	*create_philos(int numb_philos, t_rules *rules)
{
	int				i;
	t_philosopher	*philos;

	i = -1;
	philos = (t_philosopher *)malloc(sizeof(t_philosopher) * numb_philos);
	if (!philos)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_philos)
	{
		philos[i].rang = i + 1;
		philos[i].number_time_eat = 0;
		philos[i].rules = rules;
		philos[i].last_meal_time = get_time_in_ms();
		if (!init_philo_mutex(&philos[i])
			|| pthread_create(&philos[i].tid, NULL, routine, &philos[i]) != 0)
			return (cleanup(philos, NULL, i - 1), NULL);
	}
	return (philos);
}

pthread_mutex_t	*create_fork(int numb_forks)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * numb_forks);
	if (!forks)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i > 0)
				pthread_mutex_destroy(&forks[i]);
			return (free(forks), NULL);
		}
	}
	return (forks);
}
