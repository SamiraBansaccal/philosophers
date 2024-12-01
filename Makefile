# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 02:22:15 by sbansacc          #+#    #+#              #
#    Updated: 2024/11/29 02:24:36 by sbansacc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philosophers
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -fsanitize=address -g
SRCDIR		:= src/
OBJDIR		:= obj/
LIBFTDIR	:= lib/libft/
INCLFLAGS	:= -I$(SRCDIR) -I$(LIBFTDIR)
LDFLAGS		:= -L$(LIBFTDIR) -lft

SRC_FILES	:= main.c \

SRC			:= $(addprefix $(SRCDIR), $(SRC_FILES))
OBJ			:= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

LIBFT		:= $(LIBFTDIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "🚀 Houston, we have a $(NAME)!"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

$(LIBFT):
	@echo "🏗️  Building libft..."
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@echo "🧹 Cleaning up the mess..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "🧨 Obliterating all traces..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re