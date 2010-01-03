#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NFIB	5010
#define NDIG	1100

char *fib[NFIB];

void make_fib()
{
	char a[NDIG], b[NDIG], c[NDIG], *p;
	int i, k, n;

	memset(a, 0, NDIG);
	a[0] = 1;
	memset(b, 0, NDIG);

	fib[0] = "0";

	for (n = 1; n < NFIB; n++) {
		for (i = NDIG - 1; a[i] == 0; i--);

		fib[n] = (char *)malloc(i + 4);
		for (p = fib[n]; i >= 0; i--)
			*p++ = '0' + a[i];
		*p = '\0';

		for (i = 0, k = 0; i < NDIG; i++) {
			k += a[i] + b[i];
			if (k < 10) {
				c[i] = k;
				k = 0;
			} else {
				c[i] = k - 10;
				k = 1;
			}				
		}

		memcpy(b, a, NDIG);
		memcpy(a, c, NDIG);
	}
}


int main()
{
	int n;

	make_fib();

	while (scanf("%d", &n) > 0)
		printf("The Fibonacci number for %d is %s\n", n, fib[n]);

	return 0;
}
