# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 14:28:54 by earnaud           #+#    #+#              #
#    Updated: 2021/09/13 18:31:08 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
				philo_usage.c \
				threaded.c \
				utils.c \
				algo_even.c \
				check_error.c \
				sleep.c \
				forks.c \
				algo_sem.c \
				threads.c

OBJS		= $(SRCS:.c=.o)
NAME		= philo_bonus
cc			= clang
CFLAGS		= -pthread -Wall -Wextra -Werror
%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@
all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

build:
			sudo docker build -t debug-philo .

debug:		build
			sudo docker run -itv /$(shell pwd):/work debug-philo


.PHONY:		all clean fclean re
