# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 14:28:54 by earnaud           #+#    #+#              #
#    Updated: 2021/07/30 16:44:34 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c

OBJS		= $(SRCS:.c=.o)
NAME		= philo
cc			= clang
CFLAGS		= -pthread -g #-Wall -Wextra -Werror
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

.PHONY:		all clean fclean re