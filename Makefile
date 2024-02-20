#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:53:55 by bazaluga          #+#    #+#              #
#    Updated: 2024/02/20 16:09:27 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

######## SRCS & OBJ #########

INCLUDE		:=	includes/

SRCDIR		:=	src

OBJDIR		:=	obj

LIBFTDIR	:=	libft

SRC		:=	ft_printf.c node.c buffer.c buffer2.c flags_parsing.c \
			utils.c convert_buffer.c char_str_handlers.c \
			helpers.c int_handlers.c uint_handlers.c hex_handlers.c \
			ft_atol.c

OBJ		:=	$(SRC:.c=.o)

OBJD		:=	$(SRC:.c=.d)

SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

OBJ		:=	$(addprefix $(OBJDIR)/, $(OBJ))

OBJD		:=	$(addprefix $(OBJDIR)/, $(OBJD))

############ NAMES ##########

NAME		:=	libftprintf.a

LIBFTNAME	:=	libft.a

LIBFT		:=	$(LIBFTDIR)/$(LIBFTNAME)

########## COMMANDS #########

CC		:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -MMD

########### COLORS ##########

RED		:=	"\033[31m"
GREEN		:=	"\033[32m"
RESET		:=	"\033[0m"

all:		$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
		@echo $(GREEN)"Compiling "$<$(RESET)
		@$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFTDIR)/ -o $@ -c $<

$(OBJDIR):
		mkdir -p $(OBJDIR)

$(LIBFT):
		@echo $(GREEN)"Compiling libft"$(RESET)
		@make -C $(LIBFTDIR)
		@echo $(GREEN)
		cp $(LIBFT) $(NAME)
		@echo $(RESET)

$(NAME):	$(LIBFT) $(OBJ)
		@echo $(GREEN)"\nAdding obj files to lib"$(RESET)
		@ar -rcs $(NAME) $(OBJ)

bonus:		$(NAME)

-include	$(OBJD)

clean:
		@echo $(RED)"CLEANING OBJS"$(RESET)
		@rm -f $(OBJ)
		@rm -f $(OBJD)
		@make -sC libft clean

fclean:		clean
		@echo $(RED)"CLEANING ALL"$(RESET)
		@rm -f $(NAME)
		@rm -f *.out
		@rm -f $(LIBFT)
		@rm -rf *.dSYM
		@make -sC libft fclean

re:		fclean
		make all

.PHONY:		all clean fclean re
