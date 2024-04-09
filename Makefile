# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabil <nabil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 14:25:38 by nabil             #+#    #+#              #
#    Updated: 2024/04/08 15:13:38 by nabil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME		= minitalk
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(LIBFT_DIR)
RM          = rm -rf

SRC_CLIENT  = src/client.c
SRC_SERVER  = src/server.c

OBJ_DIR     = obj
OBJ_CLIENT  = $(addprefix $(OBJ_DIR)/, $(SRC_CLIENT:.c=.o))
OBJ_SERVER  = $(addprefix $(OBJ_DIR)/, $(SRC_SERVER:.c=.o))

# **************************************************************************** #
# RULES

all: $(NAME)

$(NAME): $(OBJ_CLIENT) $(OBJ_SERVER) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o client
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o server
	@echo "Compilation réussie."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) client server
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re