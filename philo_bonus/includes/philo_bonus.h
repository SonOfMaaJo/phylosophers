/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:37:58 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/30 01:33:08 by vnaoussi         ###   ########.fr       */
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
# include <signal.h>
# include <pthread.h>
# include <limits.h>

# define UTIL_ERROR "usage : philo <nb_p> <t_die> <t_eat> <t_sleep> [nb_eat]"
# define WAIT_TO_START 1
# define WAIT_TO_HOLD 1

typedef struct s_sem_phylo
{
	char	*name;
	sem_t	*sem;
}	t_sem_phylo;

typedef struct s_rules
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_eating;
	t_sem_phylo		*sem_forks;
	int				nb_philos;
	long long		start_time;
	int				is_dead;
	t_sem_phylo		*sem_dead;
	t_sem_phylo		*sem_write;
	t_sem_phylo		*sem_start;
	t_sem_phylo		*sem_stop;
	t_sem_phylo		*sem_all_eaten;
	int				start;
}	t_rules;

typedef struct s_philosopher
{
	int				rang;
	long long		last_meal_time;
	t_rules			*rules;
	pthread_t		tid;
	pid_t			pid;
	int				number_time_eat;
	t_sem_phylo		*sem_meal;
	t_sem_phylo		*sem_nb_eat;
}	t_philosopher;

int				valid(int ac, char **argv);
int				ft_atoll(const char *nptr);
t_philosopher	*create_philos(int nb_philos, t_rules *rules);
t_sem_phylo		*set_named_sem(char *name, int val);
int				destroy_sem(t_sem_phylo *sem);
void			display(char *status, t_rules *rules, int rang);
long long		get_time_in_ms(void);
void			ft_usleep(long long time_to_wait);
void			philo_loop(t_philosopher *philo);
void			cleanup(t_philosopher *philos, t_rules *rules, int i);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_itoa(int nb);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *str);
char			*set_named_sem_phylo(char **name, int pos);
void			*monitor_local(void *arg);
void			kill_all_philos(t_philosopher *philos, int nb_philos);

#endif
