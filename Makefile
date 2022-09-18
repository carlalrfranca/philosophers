# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/27 20:49:18 by cleticia          #+#    #+#              #
#    Updated: 2022/06/16 01:06:38 by cleticia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc

RM		= 	rm -rf

INC		=	-I ./inc/

FLAGS	=	-Werror -Wall -Wextra -g -pthread

SRCS	= 	src/main.c \
			src/utils.c \
			src/finish.c \
			src/routine.c \
			src/fn_utils.c \

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(INC) $(OBJS) -o $@
	@echo "Philosophers compile!"

.c.o:
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "Clean done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "All binary files deleted!"	

re:	fclean all

.PHONY: all clean fclean re
