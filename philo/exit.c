/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:26:47 by grial             #+#    #+#             */
/*   Updated: 2025/02/07 14:50:28 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	free_program(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philos)
	{
		free_philosophers(&prog->philos[i]);
		pthread_mutex_destroy(&prog->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&prog->print_status);
	if (prog->forks)
		free(prog->forks);
	if (prog->philos)
		free(prog->philos);
	prog->forks = NULL;
	prog->philos = NULL;
}

void	free_philosophers(t_philos *philos)
{
	if (philos->f_fork)
		philos->f_fork = NULL;
	if (philos->s_fork)
		philos->s_fork = NULL;
	pthread_mutex_destroy(&philos->lock);
}

void	stop_simulation(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philos)
	{
		pthread_mutex_lock(&prog->philos[i].lock);
		prog->philos[i].alive = 0;
		pthread_mutex_unlock(&prog->philos[i].lock);
		i++;
	}
}
