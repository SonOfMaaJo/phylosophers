/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valids.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:52:14 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/03 15:31:55 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int valid(int ac, char **av)
{
    int i;
    int j;

    i = 0;
    while (++i < ac)
    {
        j = -1;
        while (av[i][++j])
            if (!ft_isdigit(av[i][j]))
                return (printf("parmater should be only interger."), 0);
    }
    return (1);
}

