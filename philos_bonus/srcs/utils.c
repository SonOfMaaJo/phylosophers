/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:27 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/27 21:08:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	see_dead(t_rules *rules)
{
	int	res;

	pthread_mutex_lock(&rules->dead_lock);
	res = rules->is_dead;
	pthread_mutex_unlock(&rules->dead_lock);
	return (res);
}

void	alert_dead(t_rules *rules)
{
	pthread_mutex_lock(&rules->dead_lock);
	rules->is_dead = 1;
	pthread_mutex_unlock(&rules->dead_lock);
}

void	display(char *status, t_rules *rules, int rang)
{
	long long	time;

	pthread_mutex_lock(&rules->write_lock);
	pthread_mutex_lock(&rules->dead_lock);
	if (!rules->is_dead)
	{
		time = get_time_in_ms() - rules->start_time;
		printf("%lld %d %s", time, rang, status);
	}
	pthread_mutex_unlock(&rules->dead_lock);
	pthread_mutex_unlock(&rules->write_lock);
}

void	ft_pthread_join(t_philosopher *philos, int numb_philos)
{
	int	i;

	i = -1;
	while (++i < numb_philos)
		pthread_join(philos[i].tid, NULL);
}

void	*affectation(void *param, void *param2)
{
	(void)param;
	(void)param2;
	return (NULL);
}
