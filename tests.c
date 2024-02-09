#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "includes/ft_printf.h"

/* typedef struct flags */
/* { */
/* 	unsigned char	sharp:1; */
/* 	unsigned char	plus:1; */
/* 	unsigned char	minus:1; */
/* }				flags; */

/* #define SHARP 0x2 */
/* #define PLUS 0x4 */
/* #define MINUS 0x8 */

/* void	fct(char *str, ...) */
/* { */
/* 	va_list l; */
/* 	va_list l2; */

/* 	va_start(l, str); */
/* 	printf("1: %s\n", va_arg(l, char *)); */
/* 	va_copy(l2, l); */
/* 	int n; */
/* 	for (int i = 0; i < 3; i++) */
/* 		n = va_arg(l2, int); */
/* 	printf("asked param = %d\n", n); */
/* 	printf("2: %s\n", va_arg(l, char *)); */
/* 	va_end(l); */
/* 	va_end(l2); */
/* } */
/* typedef struct s_flags */
/* { */
/* 	unsigned char	minus:1; */
/* 	unsigned char	zero:1; */
/* 	unsigned char	dot:1; */
/* 	unsigned char	sharp:1; */
/* 	unsigned char	space:1; */
/* 	unsigned char	plus:1; */
/* 	unsigned char	min_width:1; // ? */
/* 	int				width; // for min_width, minus */
/* 	int				pad; // for dot, zero */
/* } t_flags; */
int	main(void)
{
	/* flags f; */
	/* char c = '-'; */
	/* char c2 = '+'; */

	/* f.sharp |= c == '#'; */
	/* f.plus |= c == '+'; */
	/* f.minus |= c == '-'; */
	/* f.plus |= c2 == '+'; */
	/* f.minus |= c2 == '-'; */
	/* f.sharp |= c2 == '#'; */
	/* f.sharp &= !f.plus; */
	/* fct("blabla", "str1", "str2", "str3", 8); */
	ft_printf("blabla1~%0105d~blabla2\n");
	/* printf("<%010-5d>\n", 5); */
	return 0;
}
