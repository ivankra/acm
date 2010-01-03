#include <stdio.h>

int read(int, char *, int);

int main()
{
	static char inbuf[5*131072];
	static int isdig[256];
	char *inp;
	unsigned p, t;
	long long n;

	for (p = '0'; p <= '9'; p++) isdig[p] = 1;
	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (t = 1;;) {
		while (!isdig[*inp]) inp++;
		for (p = *inp++ - '0'; isdig[*inp];) p = p * 10 + *inp++ - '0';
		if (p == 0) break;
		n = (p + (p & 1) * 3);
		printf("Case %d: %lld\n", t++, (n * n + 24) / 48);
	}

	return 0;
}
