#include <stdio.h>
#include <stdlib.h>

extern int read(int, char *, int);

char inbuf[1048576];
int isdig[256];

static inline int min(int a, int b)
{
	return (a < b) ? a : b;
}

static inline int abs(int a)
{
	return (a < 0) ? (-a) : a;
}

void main2()
{
	char *inp;
	int i, s, n, t, x1, c1, x2, c2, left, right;

	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

#define READ(x) \
	{ while (!isdig[*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; }

	for (;;) {
		READ(i);
		if (i == 0) { exit(0); }
		n = i;

		x1 = x2 = 1;
		s = c1 = c2 = 0;

		for (i = 0; i < n; i++) {
			READ(left);
			READ(right);

			t = min(c1 + abs(x1 - right), c2 + abs(x2 - right));
			c2 = min(c1 + abs(x1 - left), c2 + abs(x2 - left));
			c1 = t;

			s += (x2 = right) - (x1 = left);
		}

		c1 -= x1;
		c2 -= x2;

		s += 2 * n - 1 + ((c1 < c2) ? c1 : c2);
		printf("%d\n", s);
	}
}

int main()
{
	main2();
}
