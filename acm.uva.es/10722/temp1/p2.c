#include <stdio.h>

#define NLIMBS 24

typedef unsigned long u_int32_t;
typedef u_int32_t num_t[NLIMBS];

void set(num_t x, u_int32_t y)
{
	int i;

	for (x[0] = y, i = 0; i < NLIMBS; i++)
		x[i] = 0;
}

void add(num_t x, num_t y)
{
	int i;
	u_int32_t c;

	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 31) {
		c += x[i] + y[i];
		x[i] = c & 0x7FFFFFFF;
	}
}

void sub(num_t x, num_t y)
{
	int i;
	u_int32_t c;

	for (i = 0, c = 1; i < NLIMBS; i++, c >>= 31) {
		c += x[i] + (y[i] ^ 0x7FFFFFFF);
		x[i] = c & 0x7FFFFFFF;
	}
}

void print(num_t x)
{
	static char buf[1024], buf2[1024];
	unsigned long long r;
	int i;
	char *s;

	for (s = buf;;) {
		for (i = NLIMBS - 1, r = 0; i >= 0; i--) {
			r = (r << 31) | (unsigned long long)x[i];
			x[i] = (u_int32_t)(r / 1000000000ULL);
			r %= 1000000000ULL;
		}

		if (s == buf)
			sprintf(s, "%u", (unsigned)r);
		else
			sprintf(s, "%.9u", (unsigned)r);
		while (*s) s++;

		for (i = 0; i < NLIMBS; i++)
			if (x[i]) break;

		if (i >= NLIMBS)
			break;
	}

	for (i = 0; s-- > buf;)
		buf2[i++] = *s;
	buf2[i] = '\0';

	printf("%s\n", buf2);
}

int main()
{
	static int tab[128][128], b, n;
	register int i, k, s;

	while (scanf("%d %d", &b, &n) == 2 && b > 0) {
		for (tab[1][0] = 0, i = 1; i < b; i++)
			tab[1][i] = 1;

		for (k = 1, s = 0; k <= n;) {
			for (i = 0, s = 0; i < b; i++)
				s += tab[k][i];

			if (k++ == n)
				break;

			for (i = 0; i < b; i++)
				tab[k][i] = s;
			tab[k][3] -= tab[k - 1][1];
		}

		printf("%d\n", s);
	}

	return 0;
}
