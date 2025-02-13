/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:39:26 by grial             #+#    #+#             */
/*   Updated: 2025/02/13 13:30:50 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

t_prog	*create_program(int argc, char **argv)
{
	t_prog		*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (0);
	prog->forks = NULL;
	prog->philos = NULL;
	prog->n_philos = ft_atoi(argv[1]);
	prog->stop = 1;
	prog->time_started = time_current();
	pthread_mutex_init(&prog->print_status, NULL);
	if (argc == 6)
		prog->max_meals = ft_atoi(argv[5]);
	else
		prog->max_meals = -1;
	if (!create_forks(prog))
		return (0);
	if (!create_philosophers(prog, argv))
		return (0);
	set_fork(prog);
	return (prog);
}

int	create_philosophers(t_prog *prog, char **argv)
{
	int	i;

	i = 0;
	prog->philos = (t_philos *)malloc(sizeof(t_philos) * prog->n_philos);
	if (!prog->philos)
		return (ft_error(MSG_ERR_MALLOC));
	while (i < prog->n_philos)
	{
		prog->philos[i].philos_id = i + 1;
		prog->philos[i].meals = 0;
		prog->philos[i].alive = 1;
		prog->philos[i].printing = &prog->print_status;
		prog->philos[i].f_fork = NULL;
		prog->philos[i].s_fork = NULL;
		prog->philos[i].prog = prog;
		set_times(prog, &prog->philos[i], argv);
		pthread_mutex_init(&prog->philos[i].lock, NULL);
		i++;
	}
	return (1);
}

int	create_forks(t_prog *prog)
{
	int	i;

	i = 0;
	prog->forks = (t_fork *)malloc(sizeof(t_fork) * prog->n_philos);
	if (!prog->forks)
		return (0);
	while (i < prog->n_philos)
	{
		pthread_mutex_init(&prog->forks[i].mutex, NULL);
		i++;
	}
	return (1);
}
