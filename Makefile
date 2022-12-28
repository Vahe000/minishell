# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vasargsy <vasargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 12:39:44 by vasargsy          #+#    #+#              #
#    Updated: 2022/12/12 14:14:42 by vasargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -I./readline_vahe/include
LINKER	= -L./readline_vahe/lib -lreadline
CC		= cc
RD		= ${shell find ${HOME} -name readline_vahe 2>/dev/null}
RM		= rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LINKER) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

install:
	cd readline-master && make clean && ./configure --prefix=${RD} && make && make install

re: fclean all

.PHONY: all clean fclean re
			