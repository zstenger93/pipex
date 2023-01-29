# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 18:32:33 by zstenger          #+#    #+#              #
#    Updated: 2023/01/29 18:44:01 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
RM = rm -rf
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra

SRC = src/pipex.c \
		src/utils.c \
		src/error.c \
		src/argv_check.c\

BONUS_SRC = 

OBJS = $(SRCS:.c=.0)

BONUS_OBJS  =$(BONUS_SRCS:.c=.o)

DEF_COLOR = \033[0;39m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN = \033[1;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
CYAN2 = \x1B[1;36m

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger $(DEF_COLOR)"
	@echo "\x1B[1;36m"
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Compiling done.$(DEF_COLOR)"

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Bonus part By:$(DEF_COLOR) $(RED)zstenger $(DEF_COLOR)"
	@echo "\x1B[1;36m"
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_SRCS) $(LIBFT)
	@echo "$(PURPLE)$(NAME) $(DEF_COLOR)$(GREEN)Bonus compiling done.$(DEF_COLOR)"

clean:
	@echo "$(RED)Deleting objects.$(DEF_COLOR)"
	@echo "\x1B[1;36m"
	$(RM) $(OBJS) $(BONUS_OBJS)
	make clean -C ./libft
	@echo "$(RED)Object files have been successfully removed!\n$(DEF_COLOR)"

fclean: clean
	@echo "$(RED)Deleting objects, executables and compiled libraries.$(DEF_COLOR)"
	@echo "\x1B[1;36m"
	$(RM) $(NAME) $(BONUS_NAME)
	make fclean -C ./libft
	@echo "$(RED)\nAll executable, .o & .a files have been removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(RED)Files have been cleaned and project has been rebuilt!$(DEF_COLOR)"

.PHONY: all bonus clean fclean re