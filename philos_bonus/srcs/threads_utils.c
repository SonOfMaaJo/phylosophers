/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/27 21:05:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_try_eating(t_philosopher *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) != 0
		|| pthread_mutex_lock(second_fork) != 0)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	if (see_dead(philo->rules))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (0);
	}
	display("is eating\n", philo->rules, philo->rang);
	ft_usleep(philo->rules->time_to_eat);
	if (pthread_mutex_unlock(first_fork) != 0
		|| pthread_mutex_unlock(second_fork) != 0)
		return (0);
	return (1);
}

void	get_fork(t_philosopher *philo, pthread_mutex_t **first_fork,
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
