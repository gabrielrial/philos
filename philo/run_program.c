/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrielrial <gabrielrial@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:42:28 by grial             #+#    #+#             */
/*   Updated: 2025/02/12 21:16:44 by gabrielrial      ###   ########.fr       */
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
	if (philo->stop == 1)
		pthread_mutex_unlock(&philo->print_status);
	pthread_join(philo->monitor, NULL);
}
