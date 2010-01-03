#include <stdio.h>

int main()
{
	static int buf[128];
	int i, c, n;
	unsigned u;

	for (;;) {
		while ((c = getchar()) != EOF && (c < '0' || c > '9'));

		if (c == EOF)
			break;

		while (c == '0')
			c = getchar();

		for (i = 0; c != EOF && c >= '0' && c <= '9'; c = getchar())
			buf[i++] = c - '0';

		if (i == 0)
			break;

		n = i;

		for (u = 0, i = 0; i < n; i++)
			u += (unsigned)buf[i] * ((unsigned)(1 << (n - i)) - 1);

		printf("%u\n", u);
	}

	return 0;
}
