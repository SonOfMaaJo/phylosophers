/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/06 08:45:53 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_try_eating(t_philosopher *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) != 0 ||
			pthread_mutex_lock(second_fork) != 0)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	if (see_dead(philo->rules) && !pthread_mutex_unlock(first_fork)
			&& !pthread_mutex_unlock(second_fork))
		return (0);
	display("is eating\n", philo->rules, philo->rang);
	ft_usleep(philo->rules->time_to_eat);
	if (pthread_mutex_unlock(first_fork) != 0 ||
			pthread_mutex_unlock(second_fork) != 0)
		return (0);
	return (1);
}

static void	get_fork(t_philosopher *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->rang % 2 == 0)
	{
		*first_fork = &philo->rules->forks[philo->rang - 2];
		*second_fork = &philo->rules->forks[philo->rang - 1];
	}
	else
	{
		*first_fork = &philo->rules->forks[philo->rang - 1];
		if (philo->rang == 1)
			*second_fork = &philo->rules->forks[philo->rules->nb_forks - 1];
		else
			*second_fork = &philo->rules->forks[philo->rang - 2];
	}
}

void	philo_loop(t_philosopher *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	int	should_stop;

	should_stop = see_dead(philo->rules);
	while (should_stop == 0)
	{
		display("is thinking\n", philo->rules, philo->rang);
		ft_usleep(1);
		if (!philo_try_eating(philo, first_fork, second_fork))
			return ;
		pthread_mutex_lock(&philo->nb_eat_lock);
		philo->number_time_eat += 1;
		pthread_mutex_unlock(&philo->nb_eat_lock);
		display("is sleeping\n", philo->rules, philo->rang);
		ft_usleep(philo->rules->time_to_sleep);
		should_stop = see_dead(philo->rules);
	}
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

t_philosopher	*create_philos(int	numb_philos, t_rules *rules)
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
		philos[i].number_time_eat = 0;
		if (pthread_mutex_init(&philos[i].meal_lock, NULL) != 0
			|| pthread_mutex_init(&philos[i].nb_eat_lock, NULL) != 0)
			return (printf("error : fail to init mutex"),
					ft_free_table((void *)philos, i), NULL);
		if (pthread_create(&philos[i].tid, NULL, routine, &philos[i]) != 0)
			return (printf("error : fail to create thread."),
					ft_free_table((void *)philos, i), NULL);
	}
	return (philos);
}

pthread_mutex_t	*create_fork(int	numb_forks)
{
	int		i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * numb_forks);
	if (!forks)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (printf("error : fail to init mutex."),
					ft_free_table((void *)forks, i), NULL);
	}
	return (forks);
}
