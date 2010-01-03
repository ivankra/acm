#include <stdio.h>
#include <stdlib.h>

/* MAXN: size of inverse table; f[2000000000] = 673365 */
#define MAXN 673400

/* Table for inverse function to f(), begins as:
   0 1 2 4 6 9 12 16 20 24 29 34 39 45 51 57 63 70... */
static int tab[MAXN], tablen;

static int f(int x)
{
	register int l, h, m;

	if (x == 1)
		return 1;

	for (l = 1, h = tablen; l <= h;) {
		m = (l + h) >> 1;

		if (tab[m] <= x && (((m + 1) >= tablen) || x < tab[m + 1]))
			return m;

		if (tab[m] > x)
			h = m - 1;
		else
			l = m + 1;
	}

	fprintf(stderr, "Error: f[%d] unevaluated\n", x);
	exit(1);
}

static void mk_inverse(void)
{
	int i, j, s, k;

	for (i = 0; i < MAXN; i++)
		tab[i] = 0;
	tab[1] = 1;

	for (i = 1, s = 1, k = 0, j = 2; j < MAXN; i++) {
		tablen = j;
		k = f(i);

		if (k <= 0) {fprintf(stderr,"Error at i=%d: k=%d\n",i,k);exit(1);}

		for (; k > 0 && j < MAXN; k--) {
			s += i;
			tab[j++] = s;
		}
	}
	tablen = j;
}

int main(void)
{
	int n;

	mk_inverse();

	while (scanf("%d", &n) > 0 && n)
		printf("%d\n", f(n));

	return 0;
}
