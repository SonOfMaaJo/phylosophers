/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/28 15:35:44 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_try_eating(t_philosopher *philo)
{
	if (sem_wait(philo->rules->sem_forks->sem) == -1)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	if (philo->rules->nb_philos == 1)
		ft_usleep(philo->rules->time_to_die);
	if (see_dead(philo->rules))
		return (0);
	if (sem_wait(philo->rules->sem_forks->sem) == -1)
		return (0);
	display("taken a fork\n", philo->rules, philo->rang);
	philo->last_meal_time = get_time_in_ms();
	if (see_dead(philo->rules))
		return (0);
	display("is eating\n", philo->rules, philo->rang);
	ft_usleep(philo->rules->time_to_eat);
	if (sem_post(philo->rules->sem_forks->sem) == -1
		|| sem_post(philo->rules->sem_forks->sem) == -1);
		return (0);
	return (1);
}

void	cleanup(t_philosopher *philos, t_rules *rules, int nb_philos)
{
	int	i;

	i = -1;
	if (philos)
	{
		while (++i < nb_philos)
		{
			destroy_sem(philos[i].sem_meal);
			destroy_sem(philos[i].sem_nb_eat);
		}
	}
	i = -1;
	if (rules)
	{
		destroy_sem(rules->sem_dead);
		destroy_sem(rules->sem_write);
		destroy_sem(rules->sem_start);
		destroy_sem(rules->sem_forks);
	}
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
		if (!philo_try_eating(philo))
			return ;
		wait_sem(&philo->sem_nb_eat);
		philo->number_time_eat += 1;
		post_sem(&philo->sem_nb_eat);
		display("is sleeping\n", philo->rules, philo->rang);
		ft_usleep(philo->rules->time_to_sleep);
		should_stop = see_dead(philo->rules);
	}
}
