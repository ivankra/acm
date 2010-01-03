#include <stdio.h>
#include <string.h>

#define MAXF	2705000
#define MAXF_SQ 1647

static unsigned tab[MAXF+1];

static void mktab(void)
{
	register unsigned i, j, k;

	memset(tab, 0, sizeof(tab));

	for (i = 2; i <= MAXF; i++) {
		if (tab[i] != 0)
			continue;

		for (j = i; j <= MAXF; j += i)
			tab[j]++;

		if (i > MAXF_SQ)
			continue;

		for (k = i * i; ; k *= i) {
			for (j = k; j <= MAXF; j += k)
				tab[j]++;

			if (((long long)k * (long long)i) > (long long)MAXF)
				break;
		}
	}

	for (k = 0, i = 0; i <= MAXF; i++) {
		k += tab[i];
		tab[i] = k;
	}
}

static int solve(int n)
{
	register int a, b, c;

	if (n == 0)
		return 0;

	for (a = 0, b = MAXF; a <= b;) {
		c = (a + b) >> 1;

		if (tab[c] < n)
			a = c + 1;
		else if (tab[c] > n)
			b = c - 1;
		else
			return c;
	}

	return -1;
}

int main()
{
	int r, n, t;

	mktab();

	for (t = 1; scanf("%d", &n) == 1 && n >= 0; t++) {
		r = solve(n);

		if (r < 0)
			printf("Case %d: Not possible.\n", t);
		else
			printf("Case %d: %d!\n", t, r);
	}

	return 0;
}
