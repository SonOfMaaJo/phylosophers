/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:27 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/25 20:04:29 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_table(void	**table, int i)
{
	while (i >= 0)
		free(table[i--]);
	free(table);
}

void	see_dead(int is_dead, pthread_mutex_t *dead_lock)
{
	int	res;

	pthread_mutex_lock(dead_lock);
	res = is_dead;
	pthread_mutex_unlock(dead_lock)
	return (res);
}

void	display(char *status, pthread_mutex_t *write_lock, int rang)
{
	pthread_mutex_lock(write_lock);
	print("%ll %d %s", get_time_in_ms(), rang, status);
	pthread_mutex_unlock(write_lock);
}
