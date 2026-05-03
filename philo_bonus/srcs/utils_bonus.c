/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:27 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/30 11:35:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	see_dead(t_rules *rules)
{
	(void)rules;
	return (0);
}

void	alert_dead(t_rules *rules)
{
	(void)rules;
}

void	display(char *status, t_rules *rules, int rang)
{
	long long	time;

	sem_wait(rules->sem_write->sem);
	time = get_time_in_ms() - rules->start_time;
	printf("%lld %d %s", time, rang, status);
	fflush(stdout);
	if (status[0] != 'd')
		sem_post(rules->sem_write->sem);
}

char	*set_named_sem_phylo(char **name, int pos)
{
	char	*name_tmp;
	int		len;

	name_tmp = ft_itoa(pos);
	if (!name_tmp)
		return (NULL);
	len = ft_strlen(name_tmp) + 7;
	*name = (char *)malloc(sizeof(char) * len);
	if (!(*name))
		return (free(name_tmp), NULL);
	memset(*name, 0, len);
	ft_strlcat(*name, "/sem_", len);
	ft_strlcat(*name, name_tmp, len);
	return (free(name_tmp), *name);
}
