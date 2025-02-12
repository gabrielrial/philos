/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:19:31 by grial             #+#    #+#             */
/*   Updated: 2025/02/07 14:50:15 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	set_fork(t_prog *prog)
{
	if (prog->n_philos == 1)
		prog->philos[0].f_fork = &prog->forks[0];
	else if (prog->n_philos == 2)
	{
		prog->philos[0].f_fork = &prog->forks[1];
		prog->philos[1].f_fork = &prog->forks[1];
		prog->philos[0].s_fork = &prog->forks[0];
		prog->philos[1].s_fork = &prog->forks[0];
	}
	else 
		assign_forks(prog);
}

void	assign_forks(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philos)
	{
		if (i == prog->n_philos - 1)
		{
			prog->philos[i].f_fork = &prog->forks[0];
			prog->philos[i].s_fork = &prog->forks[i];
		}
		else
		{
			if (prog->philos[i].philos_id % 2 == 0)
			{
				prog->philos[i].f_fork = &prog->forks[i];
				prog->philos[i].s_fork = &prog->forks[i + 1];
			}
			else
			{
				prog->philos[i].s_fork = &prog->forks[i];
				prog->philos[i].f_fork = &prog->forks[i + 1];
			}
		}
		i++;
	}
}
