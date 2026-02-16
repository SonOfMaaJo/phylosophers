/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/16 19:12:22 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	void(arg);
	return (NULL);
}

t_philosopher	**create_philos(int	numb_philos)
{
	int				i;
	t_philosopher	**philos;

	i = 0;
	philos = (t_philosopher **)malloc(sizeof(t_philosopher *));
	if (!philos)
		return (printf("an allocation fail.\n"), NULL);
	while (i < numb_philos)
	{
		philos[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (!philos[i])
			return (printf("an allocation fail.\n"),
					ft_free_table((void)philos, i), NULL);
		philos[i]->status = THINKING;
		philos[i]->rang = i + 1;
		philos[i]->tid = 0;=
	}
	return (philos);
}
