#include <stdio.h>

void p(unsigned long long x)
{
	static char buf[256];
	int i;

	for (i = 0; i == 0 || x > 0; x /= 10)
		buf[i++] = (x % 10) + '0';

	while (i-- > 0)
		putchar(buf[i]);
}

int main()
{
	static unsigned long long x, d, n;
	int c;

	for (;;) {
		while ((c = getchar()) != EOF && (c < '0' || c > '9'));

		for (x = 0LL; c >= '0' && c <= '9'; c = getchar())
			x = x * 10 + c - '0';

		if (x == 0)
			break;

		for (d = 10ULL, c = 0; d-- != 0;) {
			if (((x - d) % 9ULL) != 0ULL) continue;
			n = (x - d) / 9ULL;
			n = n * 10ULL + d;
			if (c++ != 0)
				putchar(' ');
			p(n);
		}
		putchar('\n');
	}

	return 0;
}
