/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/06 09:02:51 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  inits_rules(t_rules **rules, int argc, char **argv)
{
    int nb_fork;

    *rules = (t_rules *)malloc(sizeof(t_rules));
    if (!rules)
        return (printf("An allocation fail."), 0);
    (*rules)->start_time = get_time_in_ms();
    (*rules)->time_to_die = ft_atoll(argv[2]);
    (*rules)->time_to_eat = ft_atoll(argv[3]);
    (*rules)->time_to_sleep = ft_atoll(argv[4]);
    if (argc == 6)
        (*rules)->number_of_time_eating = (int)ft_atoll(argv[5]);
    else
        (*rules)->number_of_time_eating = INT_MAX;
    nb_fork = (int)ft_atoll(argv[1]);
    (*rules)->nb_philos = nb_fork;
    if (nb_fork == 1)
        nb_fork++;
    (*rules)->forks = create_fork(nb_fork);
    (*rules)->nb_forks = nb_fork;
    if (!(*rules)->forks)
        return (free(*rules), 0);
    (*rules)->is_dead = 0;
    if (pthread_mutex_init(&(*rules)->dead_lock, NULL) != 0
            || pthread_mutex_init(&(*rules)->write_lock, NULL) != 0
                || pthread_mutex_init(&(*rules)->start_lock, NULL) != 0)
        return (free(*rules), 0);
    (*rules)->start = 0;
    return (1);
}

int check_dead(t_philosopher *philos, t_rules **rules, int *numb_eat)
{
    int result;

    result = 0;
    if (get_time_in_ms() - philos->last_meal_time > (*rules)->time_to_die)
    {
        pthread_mutex_lock(&(*rules)->write_lock);
        printf("%lld %d dead\n", get_time_in_ms() - (*rules)->start_time,
                philos->rang);
        alert_dead(*rules);
        pthread_mutex_unlock(&philos->meal_lock);
        pthread_mutex_unlock(&(*rules)->write_lock);
        result = 1;
    }
    pthread_mutex_lock(&philos->nb_eat_lock);
    if (philos->number_time_eat >= (*rules)->number_of_time_eating)
        *numb_eat += 1;
    pthread_mutex_unlock(&philos->nb_eat_lock);
    return (result);
}

static int monitoring(t_philosopher *philos, t_rules **rules)
{
    int i;
    int max_numb_philo_have_eat_nb;

    i = -1;
    pthread_mutex_lock(&(*rules)->start_lock);
    (*rules)->start = 1;
    pthread_mutex_unlock(&(*rules)->start_lock);
    while (1)
    {
        max_numb_philo_have_eat_nb = 0;
        while (++i < (*rules)->nb_philos)
        {
            pthread_mutex_lock(&philos[i].meal_lock);
            if (check_dead(&philos[i], rules, &max_numb_philo_have_eat_nb))
                return (0);
            pthread_mutex_unlock(&philos[i].meal_lock);
        }
        if (max_numb_philo_have_eat_nb == (*rules)->nb_philos)
            return (alert_dead(*rules), 0);
        i = -1;
    }
}

int main(int argc, char **argv)
{
    t_philosopher   *philos;
    t_rules         *rules;

    if (argc != 5 && argc != 6)
        return (printf(UTIL_ERROR), 1);
    if (!inits_rules(&rules, argc, argv))
        return (1);
    philos = create_philos(rules->nb_philos, rules);
    if (!philos)
        return (free(rules), 1);
    monitoring(philos, &rules);
    ft_pthread_join(philos, rules->nb_philos);
    return (0);
}
