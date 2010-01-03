#include <stdio.h>

int main()
{
	unsigned long x;

	while (scanf("%ld", (long *)&x) > 0)
		printf("%d converts to %d\n",
			x,
			((x >> 24L) & 0xFF) | ((x >> 8L) & 0xFF00) |
			((x & 0xFF00) << 8L) | ((x & 0xFF) << 24L)
		);

	return 0;
}
