#include <stdio.h>

int read(int, char *, int);

int main()
{
	static char inbuf[131072];
	static int isdig[256];
	char *inp;
	unsigned p, t;
	long long n, x, y;

	for (p = '0'; p <= '9'; p++) isdig[p] = 1;
	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (t = 1;;) {
		while (!isdig[*inp]) inp++;
		for (p = *inp++ - '0'; isdig[*inp];) p = p * 10 + *inp++ - '0';

		if (p == 0)
			break;

		x = (p + 2) / 3;
		y = (p >> 1) - ((p & 1) ^ 1);

		n = ((y - x + 1) * (3 * (x + y) - 2 * p + 2) / 2) + ((y - x + 2) / 2) + ((p + 1 - x) & 1);

		printf("Case %d: %lld\n", t++, n / 2);
	}

	return 0;
}
