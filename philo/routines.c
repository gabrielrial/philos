/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrielrial <gabrielrial@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:35:58 by grial             #+#    #+#             */
/*   Updated: 2025/02/13 21:30:44 by gabrielrial      ###   ########.fr       */
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
	pthread_mutex_lock(&philos->lock);
	time_to_sleep = philos->time_to_sleep;
	time_to_eat = philos->time_to_eat;
	time_to_think = philos->time_to_think;
	pthread_mutex_unlock(&philos->lock);
	is_ready(philos);
	pthread_mutex_lock(&philos->lock);
	if (philos->philos_id % 2 == 0)
		usleep(100);
	pthread_mutex_unlock(&philos->lock);
	while (1) 
	{
		if (!take_forks(philos))
			break ;
		if (!eating(philos, time_to_eat))
			break ;
		if (!sleeping(philos, time_to_sleep))
			break ;
		status(philos, 't');
		usleep(time_to_think);
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
	usleep(time_to_eat);
	pthread_mutex_unlock(&philos->f_fork->mutex);
	pthread_mutex_unlock(&philos->s_fork->mutex);
	if (!check_stop(philos))
		return (0);
	return (1);
}

int	sleeping(t_philos *philos, int time_to_sleep)
{
	status(philos, 's');
	pthread_mutex_lock(&philos->lock);
	philos->meals++;
	pthread_mutex_unlock(&philos->lock);
	if (!check_stop(philos))
		return (0);
	usleep(time_to_sleep);
	if (!check_stop(philos))
		return (0);
	return (1);
}
