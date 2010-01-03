#include <stdio.h>

int read(int, char *, int);

static int isdig[256], isdigm[256];

static void mktab()
{
	register int i;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	for (i = 0; i < 256; i++) isdigm[i] = isdig[i];
	isdigm['-'] = 1;
}

static int test(int c, int n)
{
	register int i;

	for (i = 0; i < n; i++)
		if ((c % n) != 1)
			return 0;
		else
			c = ((c - 1) / n) * (n - 1);

	if ((c % n) != 0)
		return 0;

	return 1;
}

int main()
{
	static char inbuf[8*1048576];
	register char *inp;
	int c, n;

	mktab();

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '-';

#define READ(var) { \
	while (!isdigm[*inp]) inp++; \
	if (*inp == '-') return 0; \
	for (var = *inp++ - '0'; isdig[*inp];) \
		var = var * 10 + *inp++ - '0'; \
}

	for (;;) {
		READ(c);

		if (c <= 1) {
			printf("%d coconuts, no solution\n", c);
		} else {
			for (n = 9; n >= 2 && !test(c, n); n--);

			if (n < 2)
				printf("%d coconuts, no solution\n", c);
			else
				printf("%d coconuts, %d people and 1 monkey\n", c, n);
		}
	}

	return 0;
}
