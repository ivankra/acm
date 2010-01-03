#include <stdio.h>

int main()
{
	unsigned n;
	int i, j;

	while (scanf("%u", &n) == 1 && n > 0) {
		printf("The parity of ");
		for (i = 31; i > 0 && ((n >> i) & 1) == 0; i--);
		for (; i >= 0; i--) putchar(((n >> i) & 1) + '0');
		for (i = 31, j = 0; i >= 0; i--) j += (n >> i) & 1;
		printf(" is %d (mod 2).\n", j);
	}

	return 0;
}
