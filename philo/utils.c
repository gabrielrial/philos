/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:55:19 by grial             #+#    #+#             */
/*   Updated: 2025/02/12 17:17:05 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

long long	time_current(void)
{
	struct timeval	tv;
	long long		current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

long long	time_program(t_philos *philos)
{
	long long	time;

	time = (time_current() - philos->time_started);
	return (time);
}

int	ft_atoi(const char *nptr)
{
	int			a;
	long long	num;
	int			sig;

	a = 0;
	sig = 1;
	num = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sig = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0');
		a = a * 10 + (*nptr - '0');
		if (num * sig > INT_MAX || num * sig < INT_MIN)
			return (0);
		nptr++;
	}
	return (a * sig);
}

void	set_times(t_prog *prog, t_philos *philos, char **argv)
{
	philos->time_started = prog->time_started;
	philos->time_last_meal = prog->time_started;
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_sleep = ft_atoi(argv[4]) * 1000;
	philos->time_to_eat = ft_atoi(argv[3]) * 1000;
	philos->time_to_think = 200;
}
