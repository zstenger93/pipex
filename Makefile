# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 18:32:33 by zstenger          #+#    #+#              #
#    Updated: 2023/02/10 15:23:57 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
RM = rm -rf
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra
DN = > /dev/null

SRC = source/mandatory/pipex.c \
		source/mandatory/path.c \
		source/mandatory/utils.c \
		source/mandatory/errors.c \
		source/mandatory/input_check.c \
		source/mandatory/open_command.c \
		source/mandatory/execute_command.c \

BONUS_SRC = source/bonus/here_doc.c \
			source/mandatory/path.c \
			source/mandatory/utils.c \
			source/mandatory/errors.c \
			source/bonus/pipex_bonus.c \
			source/mandatory/input_check.c \
			source/mandatory/open_command.c \
			source/mandatory/execute_command.c \

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)
	
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(DN)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Compiling done.$(DEF_COLOR)"
	@echo "$(CYAN3) ██▓███▒░░▒██▒░ ██▓███▒░██████▒░▒██▒░▒██▒░"
	@echo "▓██▒░░██▒░▒██▒░▓██▒░░██▒██▒░░░░░░▒██░██▒░"
	@echo "▓██▒░██▓▒░▒██▒░▓██▒░██▓▒████▒░░░░░▒███▒░"
	@echo "▒██▄█▓▒ ▒░▒██▒░▒██▄█▓▒ ▒██▒░░░░░░▒██░██▒░"
	@echo "▒██▒ ░  ░░▒██▒░▒██▒ ░  ░██████▒░▒██▒░▒██▒░"
	@echo "▒▓▒░ ░  ░░▒▓▓▒░▒▓▒░ ░ ░░░▒▓▓▓▓▒░ ▒▓▓▒ ▒▓▓▒"
	@echo "░▒ ░      ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	@echo "░░         ░░  ░░      ░   ░░     ░░   ░"
	@echo "░          ░   ░            ░     ░"

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Bonus part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_SRC) $(LIBFT) $(DN)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Bonus compiling done.$(DEF_COLOR)"
	@echo "$(RED) ██▓███▒░░▒██▒░ ██▓███▒░██████▒░▒██▒░▒██▒░"
	@echo "▓██▒░░██▒░▒██▒░▓██▒░░██▒██▒░░░░░░▒██░██▒░"
	@echo "▓██▒░██▓▒░▒██▒░▓██▒░██▓▒████▒░░░░░▒███▒░"
	@echo "▒██▄█▓▒ ▒░▒██▒░▒██▄█▓▒ ▒██▒░░░░░░▒██░██▒░"
	@echo "▒██▒ ░  ░░▒██▒░▒██▒ ░  ░██████▒░▒██▒░▒██▒░"
	@echo "▒▓▒░ ░  ░░▒▓▓▒░▒▓▒░ ░ ░░░▒▓▓▓▓▒░ ▒▓▓▒ ▒▓▓▒"
	@echo "░▒ ░      ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	@echo "░░         ░░  ░░      ░   ░░     ░░   ░"
	@echo "░          ░   ░            ░     ░"

%.o : %.c
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(CFLAGS) -c $< -o $@ $(DN)

$(LIBFT):
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(CYAN)LIBFT. $(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@git submodule update --init --recursive --remote $(DN)
	@make -C ./libft $(DN)
	@echo "$(PURPLE)LIBFT $(DEF_COLOR)$(GREEN)has been compiled.$(DEF_COLOR)"

clean:
	@echo "$(CYAN)CLEAN$(DEF_COLOR)"
	@echo "$(RED)Deleting objects.$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(RM) $(OBJS) $(BONUS_OBJS) $(DN)
	@make clean -C ./libft $(DN)
	@echo "$(RED)Object files have been successfully removed!$(DEF_COLOR)"

fclean: clean
	@echo "$(CYAN)FCLEAN$(DEF_COLOR)"
	@echo "$(RED)Deleting objects, executables and compiled libraries.$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(RM) $(NAME) $(BONUS_NAME) $(DN)
	@make fclean -C ./libft $(DN)
	@$(RM) pipex.dSYM
	@$(RM) pipex_bonus.dSYM
	@echo "$(RED)All executable, .o & .a files have been removed.$(DEF_COLOR)"

mvmem:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck ./pipex Makefile "cat" "cat" out

bvmem:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck ./pipex_bonus Makefile "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" out

re: fclean all
	@echo "$(RED)Files have been cleaned and project has been rebuilt!$(DEF_COLOR)"

DEF_COLOR = \033[0;39m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN = \033[1;96m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
CYAN2 = \x1B[1;36m

.PHONY: all bonus clean fclean re
