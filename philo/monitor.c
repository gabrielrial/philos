/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:58:41 by grial             #+#    #+#             */
/*   Updated: 2025/02/12 18:55:34 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*monitor(void *arg)
{
	int		i;
	t_prog	*prog;

	prog = (t_prog *)arg;
	i = 0;
	//usleep(1000);
	//prog->stop = 0;
	while (1)
	{
		usleep(500);
		if (i == prog->n_philos)
			i = 0;
		if (is_dead(&prog->philos[i]))
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
	static int	x = 0;

	pthread_mutex_lock(&prog->philos[x].lock);
	if (prog->philos[x].meals >= prog->max_meals)
	{
		pthread_mutex_unlock(&prog->philos[x].lock);
		x++;
	}
	else
		pthread_mutex_unlock(&prog->philos[x].lock);
	if (prog->n_philos == 1 && x == 1)
		return (1);
	else if (x == prog->n_philos - 1 && prog->n_philos > 1)
		return (1);
	return (0);
}

int	is_dead(t_philos *philos)
{
	long long	time;

	pthread_mutex_lock(&philos->lock);
	time = (time_current() - philos->time_last_meal);
	if (time >= philos->time_to_die)
	{
		status(philos, 'd');
		return (1);
	}
	pthread_mutex_unlock(&philos->lock);
	return (0);
}
