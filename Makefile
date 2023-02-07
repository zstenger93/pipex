# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 18:32:33 by zstenger          #+#    #+#              #
#    Updated: 2023/02/07 19:38:52 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
RM = rm -rf
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra

SRC = src/pipex.c \
		src/path.c \
		src/utils.c \
		src/errors.c \
		src/input_check.c \
		src/open_command.c \
		src/execute_command.c \

BONUS_SRC = src/path.c \
			src/utils.c \
			src/errors.c \
			src/input_check.c \
			src/open_command.c \
			src/bonus/here_doc.c \
			src/execute_command.c \
			src/bonus/pipex_bonus.c \

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)
	
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger $(DEF_COLOR)"
	@echo "$(CYAN2)"
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Compiling done.$(DEF_COLOR)"
	@echo "$(CYAN2) ██▓███▒░░▒██▒░ ██▓███▒░██████▒░▒██▒░▒██▒░"
	@echo "▓██▒░░██▒░▒██▒░▓██▒░░██▒██▒░░░░░░▒██░██▒░"
	@echo "▓██▒░██▓▒░▒██▒░▓██▒░██▓▒████▒░░░░░▒███▒░"
	@echo "▒██▄█▓▒ ▒░▒██▒░▒██▄█▓▒ ▒██▒░░░░░░▒██░██▒░"
	@echo "▒██▒ ░  ░░▒██▒░▒██▒ ░  ░██████▒░▒██▒░▒██▒░"
	@echo "▒▓▒░ ░  ░░▒▓▓▒░▒▓▒░ ░ ░░░▒▓▓▓▓▒░ ▒▓▓▒ ▒▓▓▒"
	@echo "░▒ ░      ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	@echo "░░         ░░  ░░      ░   ░░     ░░   ░"
	@echo "░          ░   ░            ░     ░"

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Bonus part By:$(DEF_COLOR) $(RED)zstenger $(DEF_COLOR)"
	@echo "$(CYAN2)"
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_SRC) $(LIBFT)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Bonus compiling done.$(DEF_COLOR)"

%.o : %.c
	@echo "$(CYAN2)"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(CYAN)LIBFT. $(DEF_COLOR)"
	@echo "$(CYAN2)"
#git submodule update --init --recursive --remote
	make -C ./libft
	@echo "$(PURPLE)LIBFT $(DEF_COLOR)$(GREEN)has been compiled.$(DEF_COLOR)"

clean:
	@echo "$(RED)Deleting objects.$(DEF_COLOR)"
	@echo "$(CYAN2)"
	$(RM) $(OBJS) $(BONUS_OBJS)
	make clean -C ./libft
	@echo "$(RED)Object files have been successfully removed!\n$(DEF_COLOR)"

fclean: clean
	@echo "$(RED)Deleting objects, executables and compiled libraries.$(DEF_COLOR)"
	@echo "$(CYAN2)"
	$(RM) $(NAME) $(BONUS_NAME)
	make fclean -C ./libft
	@echo "$(RED)\nAll executable, .o & .a files have been removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(RED)Files have been cleaned and project has been rebuilt!$(DEF_COLOR)"

DEF_COLOR = \033[0;39m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN = \033[1;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
CYAN2 = \x1B[1;36m

.PHONY: all bonus clean fclean re
