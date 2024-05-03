# **************************************************************************** #
#	                                                                          #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabil <nabil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 14:25:38 by nabil             #+#    #+#              #
#    Updated: 2024/05/02 22:07:58 by nabil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME            = minitalk
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
LIBFT_DIR       = libft
LIBFT           = $(LIBFT_DIR)/libft.a
INCLUDES        = -I$(LIBFT_DIR) -Isrc
RM              = rm -rf

SRC_CLIENT          = src/client.c
SRC_SERVER          = src/server.c
SRC_CLIENT_BONUS    = bonus/client_bonus.c
SRC_SERVER_BONUS    = bonus/server_bonus.c

OBJ_DIR             = obj/
OBJ_CLIENT          = $(addprefix $(OBJ_DIR)/, $(SRC_CLIENT:.c=.o))
OBJ_SERVER          = $(addprefix $(OBJ_DIR)/, $(SRC_SERVER:.c=.o))
OBJ_CLIENT_BONUS    = $(addprefix $(OBJ_DIR)/, $(SRC_CLIENT_BONUS:.c=.o))
OBJ_SERVER_BONUS    = $(addprefix $(OBJ_DIR)/, $(SRC_SERVER_BONUS:.c=.o))

# **************************************************************************** #
# COLORS
CYAN        = \033[0;36m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
END_COLOR   = \033[0m

# **************************************************************************** #
# RULES

all: client server

client: $(OBJ_CLIENT) $(LIBFT)
	@printf "$(GREEN)[Compilation]$(END_COLOR) Compiling $(CYAN)%s$(END_COLOR)..." client.c && \
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o client && \
	printf "$(GREEN)DONE$(END_COLOR)\n" && \
	echo "$(CYAN)[Minitalk]$(END_COLOR) Client is ready !"

server: $(OBJ_SERVER) $(LIBFT)
	@printf "$(GREEN)[Compilation]$(END_COLOR) Compiling $(CYAN)%s$(END_COLOR)..." server.c && \
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o server && \
	printf "$(GREEN)DONE$(END_COLOR)\n" && \
	echo "$(CYAN)[Minitalk]$(END_COLOR) Server is ready !"


$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_CLIENT): | $(OBJ_DIR)

$(OBJ_SERVER): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus: client_bonus server_bonus

client_bonus: $(OBJ_CLIENT_BONUS) $(LIBFT)
	@printf "$(GREEN)[Compilation]$(END_COLOR) Compiling $(CYAN)%s$(END_COLOR)..." client_bonus.c && \
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBFT) -o client_bonus && \
	printf "$(GREEN)DONE$(END_COLOR)\n"

server_bonus: $(OBJ_SERVER_BONUS) $(LIBFT)
	@printf "$(GREEN)[Compilation]$(END_COLOR) Compiling $(CYAN)%s$(END_COLOR)..." server_bonus.c && \
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(LIBFT) -o server_bonus && \
	printf "$(GREEN)DONE$(END_COLOR)\n"


clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) server server_bonus client client_bonus
	@$(RM) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
