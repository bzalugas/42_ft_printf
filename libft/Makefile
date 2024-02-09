#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 16:22:14 by bazaluga          #+#    #+#              #
#    Updated: 2024/02/09 02:21:31 by bazaluga         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	libft.a

SRC		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c\
			\
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c\
			\
			ft_isspace.c ft_strndup.c ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ		=	$(SRC:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -o $(<:.c=.o) -c $<


$(NAME):	$(OBJ)
			ar -rcs $(NAME) $(OBJ)

ifneq ($(shell uname), Darwin)
breaker:
			$(CC) -nostartfiles -shared -fPIC -ldl $(CFLAGS) -o libft.so $(SRC) $(SRCB)
else
breaker:
			$(CC) -dynamiclib $(CFLAGS) -o libft.so $(SRC) $(SRCB) -L../obj -lmalloc
endif

ifneq ($(shell uname), Darwin)
so:
			$(CC) -nostartfiles -shared -fPIC -ldl $(CFLAGS) -o libft.so $(SRC) $(SRCB)
else
so:
			$(CC) -dynamiclib $(CFLAGS) -o libft.so $(SRC) $(SRCB) -L../obj -lmalloc
endif

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)
			rm -f *.out
			rm -f libft.so

re:			fclean all

.PHONY:		all clean fclean re
