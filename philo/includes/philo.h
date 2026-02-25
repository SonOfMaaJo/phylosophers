/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:37:58 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/24 01:17:32 by vnaoussi         ###   ########.fr       */
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
void            *affectation(void *param, void *param2);
void            ft_usleep(int time);
int             simulation_finished(t_rules *rules);
int             mutex_lock_unlock(void *param, void *param2,
                pthread_mutex_t *mut, int (*action)(void *param,
                    void *param2));
long long       get_time_in_ms(void);
void            ft_usleep(long long time_to_wait);


typedef struct s_rules
{
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    pthread_mutex_t *forks;
    int             is_dead;
    pthread_mutex_t dead_lock;
    pthread_mutex_t write_lock;
}   t_rules


typedef struct s_philosopher
{
    int                     rang;
    long long               last_meal_time;
    pthread_mutex_t         *left_fork;
    pthread_mutex_t         *right_fork;
    t_rules                 *rules;
    pthread_t               tid;
}   t_philosopher;

#endif
