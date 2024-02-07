#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:53:55 by bazaluga          #+#    #+#              #
#    Updated: 2024/02/07 23:34:45 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	libftprintf.a

SRCDIR	=	src/

SRC		:=	ft_printf.c

SRC		:=	$(addprefix $(SRCDIR), $(SRC))

OBJDIR	=	obj/

OBJ		:=	$(SRC:.c=.o)

OBJ		:=	$(addprefix $(OBJDIR), $(OBJ))

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -o $(<:.c=.o) -c $<

$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

bonus:		$(OBJ)
			ar -rcs $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f *.out

re:			fclean all

.PHONY:		all clean fclean re
