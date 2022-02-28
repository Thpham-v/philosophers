# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thpham-v <thpham-v@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 18:56:12 by thpham-v          #+#    #+#              #
#    Updated: 2022/02/28 13:39:30 by thpham-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo
SRCS_DIR			=	./srcs/
HEADER				=	./inc/philo.h
SRCS				=	main.c				\
						init.c				\
						print_activity.c	\
						thread.c			\
						utils.c				\
						utils2.c			

SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	clang
FLAGS				=	-Wall -Wextra -Werror -I ./inc/

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread
				@echo [$(NAME)] : Created !

clean			:
				rm -f $(OBJS)
				@echo [.o] : Deleted !

fclean			:	clean
				rm -f $(NAME)
				@echo [$(NAME)] : Deleted !

re				:	fclean all

.PHONY: 		clean fclean all re