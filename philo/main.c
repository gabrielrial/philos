/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:50:30 by grial             #+#    #+#             */
/*   Updated: 2024/10/02 17:18:13 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int argc, char **argv)
{
	t_prog	*philo;

	philo = NULL;
	if (!check_arguments(argc, argv))
		return (0);
	philo = create_program(argc, argv);
	if (!philo)
		(ft_error(MSG_ERR_MALLOC));
	run_program(philo);
	free_program(philo);
	free(philo);
	philo = NULL;
	return (0);
}
