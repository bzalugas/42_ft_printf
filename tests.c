#include <stdio.h>

typedef struct flags
{
	unsigned char	sharp:1;
	unsigned char	plus:1;
	unsigned char	minus:1;
}				flags;

#define SHARP 0x2
#define PLUS 0x4
#define MINUS 0x8

int	main(void)
{
	flags f;
	char c = '-';
	char c2 = '+';

	f.sharp |= c == '#';
	f.plus |= c == '+';
	f.minus |= c == '-';
	f.plus |= c2 == '+';
	f.minus |= c2 == '-';
	f.sharp |= c2 == '#';
	f.sharp &= !f.plus;
	printf("flags status :\nsharp:%d, plus:%d, minus:%d\n", f.sharp, f.plus, f.minus);
	printf("size = %lu\n", sizeof(f));

	char infos = 0;
	infos = ((c == '-' || c2 == '-') << 3) | (c == '+' || c2 == '+') << 2 | (c == '#' || c2 == '#') << 1;
	printf("%#2x\n", infos);
	if (infos & PLUS && infos & SHARP)
		infos ^= SHARP;
	printf("%#2x\n", infos);
	for (int i = 7; i >= 0; i--)
		printf("%d ", (infos >> i)&0x1);
	printf("\n");
	return 0;
}
