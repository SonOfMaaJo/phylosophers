/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/16 19:27:31 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_philosopher   **philos;
    int             number_time_must_eat;

    if (argc < 4 || argc > 5)
        return (printf(UTIL_ERROR), 1);
    if (!valid(argv))
        return (1);
    philos = create_philos(ft_atoi(argv[1]));
    if (!philos)
        return (1);
    if (ac == 5)
        number_time_must_eat = ft_atoll(argv[4]);
    else
        number_time_must_eat = NB_MUST_EAT;
    philo_do(philos, argv, number_time_must_eat);
    return (0);
}
