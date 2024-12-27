# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 02:22:15 by sbansacc          #+#    #+#              #
#    Updated: 2024/12/27 23:49:21 by sabansac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror #-g -fsanitize=thread
SRCDIR		:= src/
OBJDIR		:= obj/
LIBFTDIR	:= lib/libft/
PRINTFDIR	:= lib/ft_printf/
INCLFLAGS	:= -I$(SRCDIR) -I$(LIBFTDIR) -I$(PRINTFDIR)
LDFLAGS		:= -L$(LIBFTDIR) -lft $(PRINTFDIR)/libftprintf.a

SRC_FILES	:= main.c init.c init_utils.c philo_routine.c check_death.c routine_utils.c \

SRC			:= $(addprefix $(SRCDIR), $(SRC_FILES))
OBJ			:= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

LIBFT		:= $(LIBFTDIR)libft.a
PRINTF		:= $(PRINTFDIR)libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "🚀 Houston, we have a $(NAME)!"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

$(LIBFT):
	@echo "🏗️  Building libft..."
	@$(MAKE) -C $(LIBFTDIR)

$(PRINTF):
	@echo "🖨️  Building ft_printf..."
	@$(MAKE) -C $(PRINTFDIR)

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