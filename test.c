#include <stdio.h>
#include "includes/ft_printf.h"

int	main()
{
	printf("<%+015.2f>\n", -23.238);
	ft_printf("<%+015.2f>\n", -23.238);
	return 0;
}
