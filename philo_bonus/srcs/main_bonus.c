/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/03 13:45:43 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_rules *rules, int nb_philos)
{
	rules->sem_forks = set_named_sem("/forks", nb_philos);
	rules->sem_dead = set_named_sem("/dead", 1);
	rules->sem_write = set_named_sem("/write", 1);
	rules->sem_stop = set_named_sem("/stop", 0);
	rules->sem_all_eaten = set_named_sem("/all_eaten", 0);
	if (!rules->sem_forks || !rules->sem_dead || !rules->sem_write
		|| !rules->sem_stop || !rules->sem_all_eaten)
	{
		destroy_sem(rules->sem_forks);
		destroy_sem(rules->sem_dead);
		destroy_sem(rules->sem_write);
		destroy_sem(rules->sem_stop);
		destroy_sem(rules->sem_all_eaten);
		return (0);
	}
	return (1);
}

static int	init_rules(t_rules **rules, int argc, char **argv)
{
	*rules = (t_rules *)malloc(sizeof(t_rules));
	if (!*rules)
		return (printf("An allocation fail."), 0);
	(*rules)->start_time = get_time_in_ms();
	(*rules)->time_to_die = ft_atoll(argv[2]);
	(*rules)->time_to_eat = ft_atoll(argv[3]);
	(*rules)->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		(*rules)->number_of_time_eating = (int)ft_atoll(argv[5]);
	else
		(*rules)->number_of_time_eating = -1;
	(*rules)->nb_philos = (int)ft_atoll(argv[1]);
	if (!init_sem(*rules, (*rules)->nb_philos))
		return (free(*rules), 0);
	(*rules)->is_dead = 0;
	return (1);
}

void	kill_all_philos(t_philosopher *philos, int nb_philos)
{
	int	i;

	i = -1;
	while (++i < nb_philos)
	{
		if (philos[i].pid > 0)
			kill(philos[i].pid, SIGKILL);
	}
}

void	*wait_all_full(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	i = -1;
	if (rules->nb_philos > 1)
		while (++i < rules->nb_philos)
			sem_wait(rules->sem_all_eaten->sem);
	sem_post(rules->sem_stop->sem);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	t_rules			*rules;
	pthread_t		full_tid;

	if (argc != 5 && argc != 6)
		return (printf(UTIL_ERROR), 1);
	if (!valid(argc, argv))
		return (1);
	if (!init_rules(&rules, argc, argv))
		return (1);
	philos = create_philos(rules->nb_philos, rules);
	if (!philos)
		return (cleanup(NULL, rules, rules->nb_philos), 1);
	if (rules->number_of_time_eating != -1)
	{
		if (pthread_create(&full_tid, NULL, wait_all_full, rules) == 0)
			pthread_detach(full_tid);
	}
	sem_wait(rules->sem_stop->sem);
	sem_post(rules->sem_write->sem);
	kill_all_philos(philos, rules->nb_philos);
	cleanup(philos, rules, rules->nb_philos);
	return (0);
}
