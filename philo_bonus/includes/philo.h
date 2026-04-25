/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:37:58 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/25 18:45:38 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define UTIL_ERROR "usage : philo <nb_p> <t_die> <t_eat> <t_sleep> [nb_eat]"
# define WAIT_TO_START 1
# define WAIT_TO_HOLD 1

typedef struct s_rules
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_eating;
	sem_t			*sem_forks;
	int				nb_philos;
	int				nb_forks;
	int				is_dead;
	long long		start_time;
	sem_t			*sem_dead;
	sem_t			*sem_ticket;
	sem_t			*sem_write;
	int				start;
}	t_rules;

typedef struct s_philosopher
{
	int				rang;
	long long		last_meal_time;
	t_rules			*rules;
	pthread_t		tid;
	int				number_time_eat;
	sem_t			*meal_lock;
	sem_t			*nb_eat_lock;
}	t_philosopher;

int				valid(int ac, char **argv);
int				ft_atoll(const char *nptr);
t_philosopher	*create_philos(int numb_philos, t_rules *rules);
int				set_named_sem(char *name, sem_t **sem, int val);
int				destroy_named(char *name, sem_t *sem);
void			*affectation(void *param, void *param2);
int				see_dead(t_rules *rules);
void			display(char *status, t_rules *rules, int rang);
long long		get_time_in_ms(void);
void			ft_usleep(long long time_to_wait);
void			alert_dead(t_rules *rules);
void			ft_pthread_join(t_philosopher *philos, int numb_philos);
void			philo_loop(t_philosopher *philo, pthread_mutex_t *f,
					pthread_mutex_t *s);
void			get_fork(t_philosopher *philo, pthread_mutex_t **f,
					pthread_mutex_t **s);
void			cleanup(t_philosopher *philos, t_rules *rules, int i);

#endif
