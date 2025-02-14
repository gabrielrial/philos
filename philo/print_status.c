/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:45:34 by grial             #+#    #+#             */
/*   Updated: 2025/02/14 17:56:31 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	status(t_philos *philos, char c)
{
	if (c == 'd')
	{
		print_status(philos, "died\n");
		return ;
	}
	pthread_mutex_lock(&philos->lock);
	pthread_mutex_lock(philos->printing);
	if (philos->alive == 1)
	{
		if (c == 'e')
			print_status(philos, "is eating\n");
		else if (c == 's')
			print_status(philos, "is sleeping\n");
		else if (c == 't')
			print_status(philos, "is thinking\n");
		else if (c == 'f')
			print_status(philos, "has taken a fork\n");
	}
	pthread_mutex_unlock(philos->printing);
	pthread_mutex_unlock(&philos->lock);
}

void	print_status(t_philos *philos, char *status)
{
	printf("%lli %i %s", time_program(philos), philos->philos_id, status);
}

int	ft_error(char *error)
{
	printf("%s", error);
	return (0);
}
