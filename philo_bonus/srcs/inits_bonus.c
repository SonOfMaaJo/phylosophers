/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/03 13:38:32 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_local(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philo->sem_meal->sem);
		if (get_time_in_ms()
			- philo->last_meal_time > philo->rules->time_to_die)
		{
			display("died\n", philo->rules, philo->rang);
			sem_post(philo->rules->sem_stop->sem);
			exit(1);
		}
		sem_post(philo->sem_meal->sem);
		usleep(philo->rules->time_to_die);
	}
	return (NULL);
}

t_sem_phylo	*set_named_sem(char *name, int val)
{
	t_sem_phylo	*sem;

	sem = (t_sem_phylo *)malloc(sizeof(t_sem_phylo));
	if (!sem)
		return (NULL);
	sem->name = ft_strdup(name);
	if (!sem->name)
		return (free(sem), NULL);
	sem_unlink(name);
	sem->sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
	if (sem->sem == SEM_FAILED)
		return (free(sem->name), free(sem), NULL);
	return (sem);
}

int	destroy_sem(t_sem_phylo *sem)
{
	if (!sem)
		return (0);
	sem_close(sem->sem);
	sem_unlink(sem->name);
	free(sem->name);
	free(sem);
	return (1);
}

static int	init_sem_phylo(t_philosopher *philo, int pos)
{
	char	*name;

	if (!set_named_sem_phylo(&name, pos))
		return (0);
	philo->sem_meal = set_named_sem(name, 1);
	free(name);
	if (!philo->sem_meal)
		return (0);
	if (!set_named_sem_phylo(&name, philo->rules->nb_philos + pos))
		return (destroy_sem(philo->sem_meal), 0);
	philo->sem_nb_eat = set_named_sem(name, 1);
	free(name);
	if (!philo->sem_nb_eat)
		return (destroy_sem(philo->sem_meal), 0);
	return (1);
}

t_philosopher	*create_philos(int nb_philos, t_rules *rules)
{
	int				i;
	t_philosopher	*philos;

	philos = (t_philosopher *)malloc(sizeof(t_philosopher) * nb_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < nb_philos)
	{
		philos[i].rang = i + 1;
		philos[i].number_time_eat = 0;
		philos[i].rules = rules;
		philos[i].last_meal_time = rules->start_time;
		philos[i].pid = -1;
		if (!init_sem_phylo(&philos[i], i))
			return (kill_all_philos(philos, i), NULL);
		philos[i].pid = fork();
		if (philos[i].pid == 0)
		{
			if (pthread_create(&philos[i].tid, NULL, monitor_local, &philos[i]))
				exit(1);
			(philo_loop(&philos[i]), exit(0));
		}
	}
	return (philos);
}
