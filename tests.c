#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "includes/ft_printf.h"

int	main(void)
{
	ft_printf("%-10c\n", 'A');
	/* printf("\n"); */
	return (printf("%-10c", 'A'));
	/* printf("%d\n", 15 % 10); */
	return (0);
}
