NAME	= minishell

O_FILES	= objects

SRCS	= $(wildcard ./source/*.c)

OBJS	= $(patsubst ./source/%.c, ./$(O_FILES)/%.o, $(SRCS))

CFLAGS	= -Wall -Wextra -Werror -g

LINKER	= -L./readline_vahe/lib -lreadline

INCLUDE	= -I ./includes -I./readline_vahe/include

CC	= cc

RD	= ${shell find ${HOME} -name readline_vahe 2>/dev/null}

RM	= rm -rf

./objects/%.o: ./source/%.c ./includes/*.h
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: $(NAME)

$(NAME): $(O_FILES) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)
	@echo "$(GRN)$(NAME) created!$(DEF)"

$(O_FILES) :
	mkdir $(O_FILES)

clean:
	@$(RM) $(OBJS)
	@echo "$(YEL)Object files deleted!$(DEF)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)All deleted!$(DEF)"

install:
	cd readline-master && make clean && ./configure --prefix=${RD} && make && make install

re: fclean all

.PHONY: all clean fclean re

#COLORS
BLK = \033[0;30m
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RED = \033[1;31m
DEF = \033[0m
