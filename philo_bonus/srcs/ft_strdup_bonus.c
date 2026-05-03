/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:56:36 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/29 16:39:49 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (copy != NULL)
	{
		while (s[i++])
			copy[i - 1] = ((char *)s)[i - 1];
		copy[i - 1] = '\0';
	}
	return (copy);
}
