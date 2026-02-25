/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:02:41 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/24 01:54:52 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_lock_unlock(void	*param, void *param2, pthread_mutex_t *mut,
		int (*action)(void *param, void	*param2))
{
	if (pthread_mutex_lock(mut) != 0)
		return (printf("error : mutex lockf."), 0)
	if (!action(param, param2))
		return (0);
	if (pthread_mutex_unlock(mut) != 0)
		return (printf("error : mutex unlock."), 0);
	return (1);
}

int	doing_philo(t_pĥilosopher *philo)
{
	long long	start_time;
	char		*status;

	start_time = get_time_in_ms();
	status = (char *)malloc(sizeof(char) * 15);
	if (!status)
		return (0);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (free(status), 0);
	if (pthread_mutex_lock(philo->right_fork) != 0
			|| simulation_finished(philo->rules))
		return (free(status), 0);
	ft_strcat(status, "has taken a fork");
	mutex_lock_unlock(&philo->rang, status, &philo->rules->write_lock, display);
	ft_strcat(status, "is eating");
	philo->last_meal_time = get_time_in_ms();
	mutex_lock_unlock(&philo->rang, status, &philo->rules->write_lock, display);
	ft_usleep(philo->rules->time_to_eat);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (free(status), 0);
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (free(status), 0);
	return (1);
}

void	*routine(void *current_philo)
{
	int				should_stop;
	t_philosopher	*philo;
	int				timestamp;
	char			*status;

	should_stop = 0;
	philo = (t_philosopher *)current_philo;
	status = (char *)malloc(sizeof(char) * 20);
	if (!status)
		return (NULL);
	mutex_lock_unlock(&should_stop, &philo->rules->is_dead,
		&philo->rules->dead_lock, affectation);
	while (should_stop == 0)
	{
		if (!doing_philo(philo))
			return (NULL);
		ft_strcat(status, "is sleeping");
		mutex_lock_unlock(&philo->rang, status, &philo->rules->write_lock, display);
		mutex_lock_unlock(&should_stop, &philo->rules->is_dead,
			&philo->rules->dead_lock, affectation);
	}
	return (NULL);
}
t_philosopher	*create_philos(int	numb_philos)
{
	int				i;
	t_philosopher	*philos;

	i = -1;
	philos = (t_philosopher *)malloc(sizeof(t_philosopher * numb_philos));
	if (!philos)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_philos)
	{
		philos[i].status = THINKING;
		philos[i].rang = i + 1;
		philos[i].tid = 0;
	}
	return (philos);
}

t_fork	*create_fork(int	numb_forks)
{
	int		i;
	t_fork	*forks;

	i = -1;
	forks = (t_fork *)malloc(sizeof(t_fork * numb_forks));
	if (!forks)
		return (printf("an allocation fail.\n"), NULL);
	while (++i < numb_forks)
	{
		if (pthread_mutex_init(forks[i]->fork, NULL) != 0)
			return (printf("error : fail to init mutex."),
					ft_free_table((void)forks, i), NULL);
	}
	return (forks);
}
