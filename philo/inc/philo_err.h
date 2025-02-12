/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_err.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grial <grial@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:33:47 by grial             #+#    #+#             */
/*   Updated: 2024/10/02 16:56:17 by grial            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERR_H
# define PHILO_ERR_H

# define MSG_ERR_ARGS	"Incorrect number of arguments.\n./philo \
 <n_philosopher> <time_to_die> <time_to_eat> <time_to_sleep> \
  <optional: n_of_meals>\n"
# define MSG_ERR_MALLOC	"Could not allocate memory.\n"
# define MSG_ERR_THREAD	"Could not create thread.\n"
# define MSG_ERR_MUTEX	"Could not create mutex.\n"
# define MSG_ERR_INPUTS	"Only digits and positive numbers.\n"
# define MSG_ERR_N_MEAL	"Number of meals must be greater than 0.\n"
# define MSG_ERR_N_PHIL	"Number of philosopher must be greater than 1.\n"

int	ft_error(char *error);

#endif