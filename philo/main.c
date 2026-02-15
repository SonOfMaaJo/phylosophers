/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:23:35 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/02/15 18:20:25 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int argc, char **argv)
{
    int nb_philo_mus_eat;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;

    if (argc < 4 || argc > 5)
        return (printf(UTIL_ERROR), 1);
    if (!valid(argc, argv))
        return (1);
    if (ac == 5)
        nb_philo_must_eat = ft_atoi(argv[ac - 1]);
    else
        nb_philo_must_eat = NB_PHILO_EAT;
    number_of_philosophers = ft_atoi(argv[1]);
    time_to_die = ft_atoll(argv[2]);
    time_to_eat = ft_atoll(argv[3]);
    time_to_sleep = ft_atoll(argv[4]);
    return (0);
}
