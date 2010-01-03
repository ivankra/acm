#include <stdio.h>

#define N 128

unsigned long a[N];

static int read()
{
	int c, i;
	unsigned long long t;

	memset(a, 0, sizeof(a));

	while ((c = getchar()) != EOF && (c < '0' || c > '9'));

	if (c == EOF) return 0;

	for (; c != EOF && c >= '0' && c <= '9'; c = getchar()) {
		for (i = 0, t = c - '0'; i < N; i++, t >>= 32)
			a[i] = (unsigned long)(t += (unsigned long long)a[i] * 10);
	}
}

static unsigned mod(unsigned m)
{
	unsigned long long c;
	int i;

	for (i = N - 1, c = 0; i >= 0; i--) {
		c = (c << 32) | (unsigned long long)a[i];
		c = c % (unsigned long long)m;
	}

	return (unsigned)c;
}

int main()
{
	int n, y, l, h, b;

	for (n = 0; read(); n++) {
		if (n > 0)
			printf("\n");

		l = (mod(4) == 0 && (mod(100) != 0 || mod(400) == 0));
		h = (mod(15) == 0);
		b = (l && mod(55) == 0);

		if (l)
			printf("This is leap year.\n");

		if (h)
			printf("This is huluculu festival year.\n");

		if (b)
			printf("This is bulukulu festival year.\n");

		if (!l && !h && !b)
			printf("This is an ordinary year.\n");
	}

	return 0;
}
