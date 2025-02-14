/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:32:29 by grial             #+#    #+#             */
/*   Updated: 2024/09/30 17:29:38 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_struct.h"
# include "philo_err.h"
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdlib.h>

long long	time_current(void);
long long	time_program(t_philos *philos);
//	ARGUMENTS
int			check_arguments(int argc, char **argv);
int			ft_isdigit(char c);

//	CREATE PROGRAM
t_prog		*create_program(int argc, char **argv);
int			create_philosophers(t_prog *prog, char **argv);
int			create_forks(t_prog *prog);

//	EXIT
void		free_program(t_prog *prog);
void		free_philosophers(t_philos *philos);
void		stop_simulation(t_prog *prog);

//	FORKS
void		set_fork(t_prog *prog);
void		assign_forks(t_prog *prog);

//	MONITOR
void		*monitor(void *arg);
int			check_stop(t_philos *philos);
int			check_meals(t_prog *prog);
int			is_dead(t_philos *philos, t_prog *prog);

//	ROUTINE
void		*routine(void *arg);
int			take_forks(t_philos *philos);
int			eating(t_philos *philos, int time_to_eat);
int			sleeping(t_philos *philos, int time_to_sleep);
int			check_stop(t_philos *philos);

//	PRINT_STATUS
void		status(t_philos *philos, char c);
void		print_status(t_philos *philos, char *status);

// ROUTINE
void		*routine(void *arg);
int			take_forks(t_philos *philos);
int			eating(t_philos *philos, int time_to_eat);
int			sleeping(t_philos *philos, int time_to_sleep);

//	RUN PROGRAM
void		run_program(t_prog *prog);

//		UTILS
int			ft_atoi(const char *nptr);
void		set_times(t_prog *prog, t_philos *philos, char **argv);
void		ft_usleep(long long time, t_philos *philo);

#endif