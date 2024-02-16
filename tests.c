#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "includes/ft_printf.h"

int	tests()
{
	int	r1;
	int	r2;

	fflush(stdout);
	r1 = printf(" <%c> \n", 'a');
	fflush(stdout);
	r2 = ft_printf(" <%c> \n", 'a');
	if (r1 != r2)
		return 0;
	fflush(stdout);
	r1 = printf(" <%5c> \n", 'a');
	fflush(stdout);
	r2 = ft_printf(" <%5c> \n", 'a');
	if (r1 != r2)
		return 0;
	fflush(stdout);
	r1 = printf(" <%-5c> \n", 'a');
	fflush(stdout);
	r2 = ft_printf(" <%-5c> \n", 'a');
	if (r1 != r2)
		return 0;
	fflush(stdout);
	r1 = printf(" <%c%c%c> \n", 'a', 'b', 'c');
	fflush(stdout);
	r2 = ft_printf(" <%c%c%c> \n", 'a', 'b', 'c');
	if (r1 != r2)
		return 0;
	return 1;
}

int	main(void)
{
	if (!tests())
	{
		printf("\n\nERROR\n");
		return (1);
	}
	printf("\n\nALL GOOD\n");
	/* ft_printf("%10d", 23); */
	return (0);
}
