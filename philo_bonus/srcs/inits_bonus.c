/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/25 18:38:19 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_sem(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->nb_eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->meal_lock);
		return (0);
	}
	return (1);
}

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
	{
		get_fork(philo, &first_fork, &second_fork);
		philo_loop(philo, first_fork, second_fork);
	}
	return (NULL);
}

int	set_named_sem(char *name, sem_t **sem, int val)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
	if (*sem == SEM_FAILED)
		return (0);
	return (1);
}

int	destroy_named(char *name, sem_t *sem)
{
	int	error;

	error = 0;
	if (sem_close(sem) == -1)
		error = 1;
	if (sem_unlink(name) != -1 && !error)
		return (1);
	return (0);
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
		if (!init_philo_sem(&philos[i])
			|| pthread_create(&philos[i].tid, NULL, routine, &philos[i]) != 0)
			return (cleanup(philos, NULL, i - 1), NULL);
	}
	return (philos);
}
