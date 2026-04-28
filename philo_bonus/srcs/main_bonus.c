/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/28 15:55:39 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
int	init_sem(t_rules *rules, int nb_forks)
{
	rules->sem_forks = set_named_sem("/forks", nb_forks);
	if (!sem_forks)
		return (0);
	rules->sem_dead = set_named_sem("/dead", 1);
	if (!rules->sem_dead)
		return (destroy_sem(rules->sem_forks), 0);
	rules->sem_write = set_named_sem("/write", 1);
	if (!rules->sem_write)
		return (destroy_sem(rules->sem_forks), destroy_sem(rules->sem_dead), 0);
	rules->sem_start = set_named_sem("/start", 1);
	if (!rules->sem_start)
		return (destroy_sem(rules->sem_forks), destroy_sem(rules->sem_dead),
				destroy(rules->sem_write), 0);
	rules->sem_nb_eat
	return (1);
}

static int	init_rules(t_rules **rules, int argc, char **argv)
{
	int	nb_philos;

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
		(*rules)->number_of_time_eating = INT_MAX;
	nb_philos = (int)ft_atoll(argv[1]);
	(*rules)->nb_philos = nb_philos;
	(*rules)->nb_forks = nb_philos;
	if (!init_sem(*rules))
		return (free(*rules), 0);
	(*rules)->is_dead = 0;
	(*rules)->start = 0;
	return (1);
}

int	check_dead(t_philosopher *philos, t_rules **rules, int *numb_eat)
{
	int	result;

	result = 0;
	sem_wait(philo->sem_meal->sem);
	if (get_time_in_ms() - philos->last_meal_time > (*rules)->time_to_die)
	{
		sem_wait(&(*rules)->sem_write->sem);
		printf("%lld %d dead\n", get_time_in_ms() - (*rules)->start_time,
			philos->rang);
		alert_dead(*rules);
		result = 1;
	}
	sem_post(philo->sem_meal->sem);
	sem_wait(philo->sem_nb_eat->sem);
	if (philos->number_time_eat >= (*rules)->number_of_time_eating)
		*numb_eat += 1;
	sem_post(philo->sem_nb_eat->sem);
	return (result);
}

static int	monitoring(t_philosopher *philos, t_rules **rules)
{
	int	i;
	int	max_numb_philo_have_eat_nb;

	i = -1;
	(*rules)->start = 1;
	while (1)
	{
		max_numb_philo_have_eat_nb = 0;
		while (++i < (*rules)->nb_philos)
			if (check_dead(&philos[i], rules, &max_numb_philo_have_eat_nb))
				return (0);
		if (max_numb_philo_have_eat_nb == (*rules)->nb_philos)
			return (alert_dead(*rules), 0);
		i = -1;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	t_rules			*rules;

	if (argc != 5 && argc != 6)
		return (printf(UTIL_ERROR), 1);
	if (!valid(argc, argv))
		return (1);
	if (!init_rules(&rules, argc, argv))
		return (1);
	philos = create_philos(rules->nb_philos, rules);
	if (!philos)
		return (cleanup(NULL, rules, rules->nb_philos), 1);
	monitoring(philos, &rules);
	ft_pthread_join(philos, rules->nb_philos);
	cleanup(philos, rules, rules->nb_philos);
	return (0);
}
