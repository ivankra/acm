#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXN 1001000
#define ISCOMPOSITE(n) ((sieve[(n) >> 3] >> ((n) & 7)) & 1)

unsigned char sieve[(MAXN + 7) / 8];
int table[MAXN];

static void make_sieve()
{
	register int i, j;

	memset(sieve, 0, sizeof(sieve));

	for (i = 2; i < MAXN; i++) {
		if ((sieve[i >> 3] >> (i & 7)) & 1)
			continue;
		for (j = i + i; j < MAXN; j += i)
			sieve[j >> 3] |= 1 << (j & 7);
	}
}

static void make_table()
{
	register int i, j, s, k;
	int d[10];

	make_sieve();

	table[0] = 0;
	table[1] = 0;
	table[2] = 1;

	for (i = 0; i < 10; i++)
		d[i] = 0;
	d[0] = 3;

	for (i = 3, s = 3, k = 1; i < MAXN; i += 2) {
		if (!ISCOMPOSITE(i) && !ISCOMPOSITE(s))
			k++;

		table[i] = k;
		table[i + 1] = k;

		d[0] += 2;
		s += 2;
		for (j = 0;;) {
			if (d[j] < 10)
				break;
			d[j++] -= 10;
			d[j]++;
			s -= 9;
		}
	}
}

int main()
{
	int l, r, n;

	make_table();

	scanf("%d", &n);
	while (n-- > 0 && scanf("%d %d", &l, &r) >= 2) {
		if (l < 1) l = 1;
		printf("%d\n", table[r] - table[l - 1]);
	}

	return 0;
}
