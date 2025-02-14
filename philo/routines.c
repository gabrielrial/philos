/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:35:58 by grial             #+#    #+#             */
/*   Updated: 2025/02/14 17:27:18 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	is_ready(t_philos *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->prog->program_monitor);
		if (philo->prog->stop == 0)
		{
			pthread_mutex_unlock(&philo->prog->program_monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->prog->program_monitor);
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_philos	*philos;
	int			time_to_eat;
	int			time_to_think;
	int			time_to_sleep;

	philos = (t_philos *)arg;
	time_to_sleep = philos->time_to_sleep / 1000;
	time_to_eat = philos->time_to_eat / 1000;
	time_to_think = philos->time_to_think / 1000;
	is_ready(philos);
	if (philos->philos_id % 2 == 0)
		usleep(100);
	while (1) 
	{
		if (!take_forks(philos))
			break ;
		if (!eating(philos, time_to_eat))
			break ;
		if (!sleeping(philos, time_to_sleep))
			break ;
		status(philos, 't');
		ft_usleep(time_to_think, philos);
	}
	return (NULL);
}

int	take_forks(t_philos *philos)
{
	pthread_mutex_lock(&philos->f_fork->mutex);
	if (!check_stop(philos))
	{
		pthread_mutex_unlock(&philos->f_fork->mutex);
		return (0);
	}
	status(philos, 'f');
	if (!philos->s_fork)
	{
		usleep(philos->time_to_die * 1000);
		pthread_mutex_unlock(&philos->f_fork->mutex);
		pthread_mutex_unlock(&philos->lock);
		return (0);
	}
	pthread_mutex_lock(&philos->s_fork->mutex);
	if (!check_stop(philos))
	{
		pthread_mutex_unlock(&philos->s_fork->mutex);
		pthread_mutex_unlock(&philos->f_fork->mutex);
		return (0);
	}
	status(philos, 'f');
	return (1);
}

int	eating(t_philos *philos, int time_to_eat)
{
	status(philos, 'e');
	pthread_mutex_lock(&philos->lock);
	philos->time_last_meal = time_current();
	pthread_mutex_unlock(&philos->lock);
	ft_usleep(time_to_eat, philos);
	pthread_mutex_unlock(&philos->f_fork->mutex);
	pthread_mutex_unlock(&philos->s_fork->mutex);
	pthread_mutex_lock(&philos->lock);
	philos->meals++;
	pthread_mutex_unlock(&philos->lock);
	if (!check_stop(philos))
		return (0);
	return (1);
}

int	sleeping(t_philos *philos, int time_to_sleep)
{
	status(philos, 's');
	if (!check_stop(philos))
		return (0);
	ft_usleep(time_to_sleep, philos);
	if (!check_stop(philos))
		return (0);
	return (1);
}
