#include <stdio.h>

static int rtab[256];
static int stab[31800], stab_len;

#define PERFECT(n) (rtab[(n) & 0xFF] && perfect_square1(n))

static int perfect_square1(int n)
{
	register int a, b, c;

	for (a = 0, b = stab_len - 1; a < b;) {
		c = (a + b) >> 1;

		if (stab[c] < n)
			a = c + 1;
		else if (stab[c] > n)
			b = c - 1;
		else
			return 1;
	}

	return (stab[a] == n);
}

int main()
{
	static int d[128], n;
	register int i, j, k;

	for (i = 0; i < 256; i++)
		rtab[i] = 0;

	for (i = 0; i < 256; i++)
		rtab[(i * i) & 0xFF] = 1;

	for (i = 0, j = 0; j <= 1000000000; i++) {
		stab[i] = j;
		j += 2 * i + 1;
	}
	stab_len = i;

	for (;;) {
		while ((j = getchar()) != EOF && (j < '0' || j > '9'));

		while (j == '0')
			j = getchar();

		for (n = 0; j >= '0' && j <= '9'; j = getchar())
			d[n++] = (j - '0');

		if (n == 0)
			break;

		for (j = 2, i = 0; i < n; i++)
			if (d[i] >= j)
				j = d[i] + 1;

		for (; j <= 100; j++) {
			for (k = 0, i = 0; i < n; i++)
				k = k * j + d[i];

			if (PERFECT(k))
				break;
		}

		printf("%d\n", j);
	}

	return 0;
}
