/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/28 15:53:11 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*routine(void *current_philo)
{
	t_philosopher	*philo;
	int				pid;

	philo = (t_philosopher *)current_philo;
	while (1)
		if (philo->rules->start)
			break ;
	pid = fork();
	if (pid == 0)
		philo_loop(philo);
	else
	{
		while (1)
		{
			ft_usleep(1);
			if (see_dead(philo->rules))
				break;
		}
		kill(pid);
	}
	return (NULL);
}

t_sem_phylo *set_named_sem(char *name, int val)
{
	t_sem_phylo	*sem;

	sem = (t_sem_phylo *)malloc(sizeof(t_sem_phylo));
	if (!sem)
		return (NULL);
	sem->name = ft_strdup(name);
	if (!sem->name)
		return (free(sem), NULL);
	sem->sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
	if (sem->sem == SEM_FAILED)
		return (free(sem->name), free(sem), NULL);
	return (sem);
}

int	destroy_sem(t_sem_phylo *sem)
{
	int	error;

	error = 0;
	if (!sem)
		return (0);
	if (sem_close(sem->sem) == -1)
		error = 1;
	if (sem_unlink(sem->name) != -1 && !error)
		return (free(sem->name), 1);
	return (free(sem->name), free(sem), 0);
}

t_philosopher	*create_philos(int numb_philos, t_rules *rules)
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
		init_sem_phylo(philos + i, i);
		if (pthread_create(&philos[i].tid, NULL, routine, &philos[i]) != 0)
			return (cleanup(philos, NULL, i - 1), NULL);
	}
	return (philos);
}
