#include <stdio.h>

int read(int, char *, int);

static int min(int a, int b)
{
	return (a < b) ? a : b;
}

static int abs(int a)
{
	return (a < 0) ? (-a) : a;
}

int main()
{
	static char inbuf[1048576];
	static int isdig[256];
	char *inp;
	int i, n, s, t, x1, c1, x2, c2, left, right;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

#define READ(x) \
	{ while (!isdig[*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; }

	for (;;) {
		READ(n);
		if (n == 0) break;

		x1 = x2 = 1;
		c1 = c2 = 0;
		s = 0;

		for (i = 1; i <= n; i++) {
			READ(left);
			READ(right);

			t = min(c1 + abs(x1 - right), c2 + abs(x2 - right));
			c2 = min(c1 + abs(x1 - left), c2 + abs(x2 - left));
			c1 = t;

			s += right - left;

			x1 = left;
			x2 = right;
		}

		s += n - 1 + min(c1 + n - x1, c2 + n - x2);
		printf("%d\n", s);
	}

	return 0;
}
