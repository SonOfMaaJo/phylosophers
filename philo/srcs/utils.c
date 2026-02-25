/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:27 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/24 02:04:05 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_table(void	**table, int i)
{
	while (i >= 0)
		free(table[i--]);
	free(table);
}

void	*affectation(void *param, void *param2)
{
	*param = *param2;
	return (param2);
}

int	simulation_finished(t_rules *rules)
{
	int	res;

	mutex_lock_unlock(&res, &rules->is_dead, &data->dead_lock, affectation);
	return (res);
}

void	*display(void *param, void *param2)
{
	print("%ll %d %s", get_time_in_ms(), *param, param2)
}
