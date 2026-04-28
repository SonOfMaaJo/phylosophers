/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:27 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/28 14:54:55 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	see_dead(t_rules *rules)
{
	int	res;

	sem_wait(rules->sem_dead->sem);
	res = rules->is_dead;
	sem_post(rules->sem_dead->sem);
	return (res);
}

void	alert_dead(t_rules *rules)
{
	sem_wait(rules->sem_dead->sem)
	rules->is_dead = 1;
	sem_post(rules->sem_dead->sem);
}

void	display(char *status, t_rules *rules, int rang)
{
	long long	time;

	sem_wait(rules->sem_write->sem);
	sem_wait(rules->sem_dead->sem);
	if (!rules->is_dead)
	{
		time = get_time_in_ms() - rules->start_time;
		printf("%lld %d %s", time, rang, status);
	}
	pthread_mutex_unlock(rules->sem_dead->sem);
	pthread_mutex_unlock(rules->sem_write->sem);
}

void	ft_pthread_join(t_philosopher *philos, int numb_philos)
{
	int	i;

	i = -1;
	while (++i < numb_philos)
		pthread_join(philos[i].tid, NULL);
}
