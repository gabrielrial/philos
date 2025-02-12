# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grial <grial@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 17:57:09 by grial             #+#    #+#              #
#    Updated: 2024/10/02 17:22:03 by grial            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	main.c create_program.c run_program.c routines.c arguments.c monitor.c exit.c utils.c print_status.c forks.c

OBJS = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all