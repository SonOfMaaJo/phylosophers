/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:37:58 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/16 19:28:42 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# define UTIL_ERROR "usage : <number_of_philosophers> <time_to_die> \
    <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]"
# define NB_MUST_EAT 0
# define SLEEPING -1
# define THINKING 0
# define EATING 1

int             valid(int ac, char **argv);
t_philosopher   **create_philos(int numb_philos);
void            ft_free_table(void **table, int i);
void            *routine(void *arg);
void            *do_philo(t_philosopher **philos, char **argv, int nb_m_eat);

typedef struct s_philosopher
{
    int                     rang;
    int                     status;
    pthread_t               tid;
}   t_philosopher;

#endif
