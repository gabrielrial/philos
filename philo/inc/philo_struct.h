/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:52:32 by grial             #+#    #+#             */
/*   Updated: 2024/10/02 17:17:25 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

# include <pthread.h>

typedef struct s_program	t_prog;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				philos_id;
	int				meals;
	long long		time_started;
	long long		alive;
	long long		time_last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	void			*printing;
	t_fork			*f_fork;
	t_fork			*s_fork;
	pthread_mutex_t	lock;
	pthread_t		thread;
}	t_philos;

typedef struct s_program
{
	int				n_philos;
	int				max_meals;
	int				stop;
	long long		time_started;
	t_fork			*forks;
	t_philos		*philos;
	pthread_t		monitor;
	pthread_mutex_t	print_status;
	pthread_mutex_t	program_monitor;
}	t_prog;

#endif