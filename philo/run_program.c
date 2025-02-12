/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:42:28 by grial             #+#    #+#             */
/*   Updated: 2024/10/02 17:05:55 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	run_program(t_prog *philo)
{
	int	i;

	i = 0;
	pthread_create(&philo->monitor, NULL, &monitor, philo);
	while (i < philo->n_philos)
	{
		philo->philos[i].time_started = time_current();
		pthread_create(&philo->philos[i].thread, NULL, 
			&routine, &philo->philos[i]);
		i++;
	}
	i = 0;
	while (i < philo->n_philos)
	{
		pthread_join(philo->philos[i].thread, NULL);
		i++;
	}
	pthread_join(philo->monitor, NULL);
}
