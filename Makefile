# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 18:32:33 by zstenger          #+#    #+#              #
#    Updated: 2023/03/03 08:47:18 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = gcc
RM = rm -rf
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra
DN = > /dev/null
SRC_DIR = source/
OBJ_DIR = objects/

SRC = mandatory/pipex \
		mandatory/path \
		mandatory/utils \
		mandatory/errors \
		mandatory/input_check \
		mandatory/open_command \
		mandatory/cmd_validator \
		mandatory/execute_command \

BONUS_SRC = bonus/here_doc \
			mandatory/path \
			mandatory/utils \
			mandatory/errors \
			bonus/pipex_bonus \
			mandatory/input_check \
			mandatory/open_command \
			mandatory/cmd_validator \
			mandatory/execute_command \

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
BONUS_SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(BONUS_SRC)))
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BONUS_SRC)))

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME) $(DN)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Compiling done.$(DEF_COLOR)"
	@echo "$(CYAN3) ██▓███▒░░▒██▒░ ██▓███▒░██████▒░▒██▒░▒██▒░"
	@echo "▓██▒░░██▒░▒██▒░▓██▒░░██▒██▒░░░░░░▒██░██▒░"
	@echo "▓██▒░██▓▒░▒██▒░▓██▒░██▓▒████▒░░░░░▒███▒░"
	@echo "▒██▄█▓▒ ▒░▒██▒░▒██▄█▓▒ ▒██▒░░░░░░▒██░██▒░"
	@echo "▒██▒ ░  ░░▒██▒░▒██▒ ░  ░██████▒░▒██▒░▒██▒░"
	@echo "▒▓▒░ ░  ░░▒▓▓▒░▒▓▒░ ░ ░░░▒▓▓▓▓▒░░▒▓▓▒ ▒▓▓▒"
	@echo "░▒ ░      ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	@echo "░░         ░░  ░░      ░   ░░     ░░   ░"
	@echo "░          ░   ░            ░     ░"
	@echo ""
	@curl https://icanhazdadjoke.com
	@echo ""
	@echo ""

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Bonus part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(CC) $(CFLAGS) $(LIBFT) $(BONUS_OBJS) -o $(BONUS_NAME) $(DN)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Bonus compiling done.$(DEF_COLOR)"
	@echo "$(RED) ██▓███▒░░▒██▒░ ██▓███▒░██████▒░▒██▒░▒██▒░"
	@echo "▓██▒░░██▒░▒██▒░▓██▒░░██▒██▒░░░░░░▒██░██▒░"
	@echo "▓██▒░██▓▒░▒██▒░▓██▒░██▓▒████▒░░░░░▒███▒░"
	@echo "▒██▄█▓▒ ▒░▒██▒░▒██▄█▓▒ ▒██▒░░░░░░▒██░██▒░"
	@echo "▒██▒ ░  ░░▒██▒░▒██▒ ░  ░██████▒░▒██▒░▒██▒░"
	@echo "▒▓▒░ ░  ░░▒▓▓▒░▒▓▒░ ░ ░░░▒▓▓▓▓▒░░▒▓▓▒ ▒▓▓▒"
	@echo "░▒ ░      ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	@echo "░░         ░░  ░░      ░   ░░     ░░   ░"
	@echo "░          ░   ░            ░     ░"
	@echo ""
	@curl https://icanhazdadjoke.com
	@echo ""
	@echo ""

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
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
	@$(RM) $(OBJ_DIR) $(BONUS_OBJS) $(DN)
	@make clean -C ./libft $(DN)
	@echo "$(RED)Object files have been successfully removed!$(DEF_COLOR)"

fclean:
	@make clean $(DN)
	@echo "$(CYAN)FCLEAN$(DEF_COLOR)"
	@echo "$(RED)Deleting objects, executables.$(DEF_COLOR)"
	@echo "$(CYAN2)" $(DN)
	@$(RM) $(NAME) $(BONUS_NAME) $(DN)
	@make fclean -C ./libft $(DN)
	@$(RM) pipex.dSYM $(DN)
	@$(RM) pipex_bonus.dSYM $(DN)
	@echo "$(RED)Executable and object files have been successfully removed.$(DEF_COLOR)"

mvmem:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck ./pipex Makefile "cat" "cat" out

bvmem:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck ./pipex_bonus Makefile "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" out

np:
	@env -i ./pipex Makefile "cat" "cat" out

npb:
	@env -i ./pipex_bonus Makefile "cat" "cat" "cat" "cat" "cat" "cat" "cat" "cat" out

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

.PHONY: all bonus clean fclean re mvmem bvmem np npb