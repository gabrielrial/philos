/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:58:41 by grial             #+#    #+#             */
/*   Updated: 2025/02/14 17:59:50 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*monitor(void *arg)
{
	int		i;
	t_prog	*prog;

	prog = (t_prog *)arg;
	i = 0;
	usleep(1000);
	pthread_mutex_lock(&prog->program_monitor);
	prog->stop = 0;
	pthread_mutex_unlock(&prog->program_monitor);
	while (1)
	{
		usleep(100);
		if (i == prog->n_philos)
			i = 0;
		if (is_dead(&prog->philos[i], prog))
			break ;
		if (prog->max_meals > 0 && check_meals(prog))
			break ;
		i++;
	}
	stop_simulation(prog);
	return (NULL);
}

int	check_stop(t_philos *philos)
{
	pthread_mutex_lock(&philos->lock);
	if (philos->alive == 0)
	{
		pthread_mutex_unlock(&philos->lock);
		return (0);
	}
	pthread_mutex_unlock(&philos->lock);
	return (1);
}

int	check_meals(t_prog *prog)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (i < prog->n_philos)
	{
		pthread_mutex_lock(&prog->philos[i].lock);
		if (prog->philos[i].meals >= prog->max_meals)
			x++;
		pthread_mutex_unlock(&prog->philos[i].lock);
		i++;
	}
	if ((prog->n_philos == 1 && x == 1) || (x == prog->n_philos))
	{
		prog->stop = 1;
		return (1);
	}
	return (0);
}

int	is_dead(t_philos *philos, t_prog *prog)
{
	long long	time;

	pthread_mutex_lock(&philos->lock);
	time = (time_current() - philos->time_last_meal);
	if (time >= philos->time_to_die)
	{
		philos->alive = 0;
		pthread_mutex_unlock(&philos->lock);
		pthread_mutex_lock(&prog->print_status);
		status(philos, 'd');
		pthread_mutex_unlock(&prog->print_status);
		return (1);
	}
	pthread_mutex_unlock(&philos->lock);
	return (0);
}
