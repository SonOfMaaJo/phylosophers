/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/03 15:34:40 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_try_eating(t_philosopher *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	if (pthread_mutex_lock(first_fork) != 0)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	if (philo->rules->nb_philos == 1)
		ft_usleep(philo->rules->time_to_die);
	if (see_dead(philo->rules))
		return (pthread_mutex_unlock(first_fork), 0);
	if (pthread_mutex_lock(second_fork) != 0)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	if (see_dead(philo->rules))
		return (pthread_mutex_unlock(first_fork),
			pthread_mutex_unlock(second_fork), 0);
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
	if (philo->rules->nb_forks == 1)
	{
		*first_fork = &philo->rules->forks[philo->rang - 1];
		*second_fork = &philo->rules->forks[philo->rang - 1];
		return ;
	}
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

void	cleanup(t_philosopher *philos, t_rules *rules, int nb_philos)
{
	int	i;

	i = -1;
	if (philos)
	{
		while (++i < nb_philos)
		{
			pthread_mutex_destroy(&philos[i].meal_lock);
			pthread_mutex_destroy(&philos[i].nb_eat_lock);
		}
	}
	i = -1;
	if (rules)
		while (++i < rules->nb_forks)
			pthread_mutex_destroy(&rules->forks[i]);
	pthread_mutex_destroy(&rules->dead_lock);
	pthread_mutex_destroy(&rules->write_lock);
	pthread_mutex_destroy(&rules->start_lock);
	free(rules->forks);
	free(philos);
	free(rules);
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
