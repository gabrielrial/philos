/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:21:00 by grial             #+#    #+#             */
/*   Updated: 2024/09/30 15:56:01 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	check_arguments(int argc, char **argv)
{
	int	x;
	int	y;

	if (argc != 5 && argc != 6)
		return (ft_error(MSG_ERR_ARGS));
	if (argc == 6 && argv[5][0] == '0')
		return (ft_error(MSG_ERR_N_MEAL));
	if (argv[1][0] == '0')
		return (ft_error(MSG_ERR_N_PHIL));
	x = 1;
	while (argv[x])
	{
		y = 0;
		while (argv[x][y])
		{
			if (!ft_isdigit(argv[x][y]))
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (ft_error(MSG_ERR_INPUTS));
}
