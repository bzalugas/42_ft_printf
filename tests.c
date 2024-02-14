#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "includes/ft_printf.h"

int	main(void)
{
	/* return (ft_printf("%.1s", "abc")); */
	printf("%.*$2$d", 3, 12, 4);
	/* return (printf("%-10.1s", "abcde")); */
	/* printf("%d\n", 15 % 10); */
	return (0);
}
