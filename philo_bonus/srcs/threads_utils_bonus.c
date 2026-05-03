/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/03 13:42:22 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_try_eating(t_philosopher *philo)
{
	sem_wait(philo->rules->sem_forks->sem);
	display("has taken a fork\n", philo->rules, philo->rang);
	if (philo->rules->nb_philos == 1)
		return (ft_usleep(philo->rules->time_to_die), 0);
	sem_wait(philo->rules->sem_forks->sem);
	display("has taken a fork\n", philo->rules, philo->rang);
	sem_wait(philo->sem_meal->sem);
	philo->last_meal_time = get_time_in_ms();
	sem_post(philo->sem_meal->sem);
	display("is eating\n", philo->rules, philo->rang);
	ft_usleep(philo->rules->time_to_eat);
	sem_post(philo->rules->sem_forks->sem);
	sem_post(philo->rules->sem_forks->sem);
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
		free(philos);
	}
	if (rules)
	{
		destroy_sem(rules->sem_dead);
		destroy_sem(rules->sem_write);
		destroy_sem(rules->sem_forks);
		destroy_sem(rules->sem_stop);
		destroy_sem(rules->sem_all_eaten);
		free(rules);
	}
}

void	philo_loop(t_philosopher *philo)
{
	if (philo->rang % 2 == 0)
		ft_usleep(philo->rules->time_to_eat / 2);
	while (1)
	{
		display("is thinking\n", philo->rules, philo->rang);
		if (!philo_try_eating(philo))
			break ;
		philo->number_time_eat++;
		if (philo->rules->number_of_time_eating != -1
			&& philo->number_time_eat >= philo->rules->number_of_time_eating)
		{
			sem_post(philo->rules->sem_all_eaten->sem);
			break ;
		}
		display("is sleeping\n", philo->rules, philo->rang);
		ft_usleep(philo->rules->time_to_sleep);
	}
	ft_usleep(philo->rules->time_to_die);
}
