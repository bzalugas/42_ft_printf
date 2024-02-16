#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:53:55 by bazaluga          #+#    #+#              #
#    Updated: 2024/02/16 22:50:35 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

######## SRCS & OBJ #########

INCLUDE		:=	includes/

SRCDIR		:=	src

OBJDIR		:=	obj

LIBFTDIR	:=	libft

SRC		:=	ft_printf.c node.c buffer.c buffer2.c flags_parsing.c \
			utils.c convert_buffer.c char_str_handlers.c \
			helpers.c int_handlers.c uint_handlers.c

OBJ		:=	$(SRC:.c=.o)

SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

OBJ		:=	$(addprefix $(OBJDIR)/, $(OBJ))

############ NAMES ##########

NAME		:=	libftprintf.a

LIBFTNAME	:=	libft.a

LIBFT		:=	$(LIBFTDIR)/$(LIBFTNAME)

########## COMMANDS #########

CC		:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -g3

########### COLORS ##########

RED		:=	"\033[31m"
GREEN		:=	"\033[32m"
RESET		:=	"\033[0m"

all:		$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFTDIR)/ -o $@ -c $<

$(OBJDIR):
		mkdir -p $(OBJDIR)

$(LIBFT):
		@echo $(GREEN)"Compiling libft"$(RESET)
		make -C $(LIBFTDIR)
		cp $(LIBFT) $(NAME)

$(NAME):	$(LIBFT) $(OBJDIR) $(OBJ)
		ar -rcs $(NAME) $(OBJ)

bonus:		$(OBJ)
		ar -rcs $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)
		rm -f *.out
		rm -f $(LIBFT)
		rm -rf *.dSYM

re:		fclean all

.PHONY:		all clean fclean re
