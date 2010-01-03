#include <stdio.h>
#include <assert.h>

#define EPS 1e-8

/* rows are numbered 0,1,...,n-1
   columns: 0,1,...,m-1 */

int n, m;
double P[8][8];

int fgot[8][256], id;
double ftab[8][256];

/* returns the probability of generating a valid maze, provided that
   the rows 0,1,...,r-1 have already been generated, and there's path from
   (0,0) to (r-1,i) if ((A >> i) & 1) == 1 */
double f(int r, int A)
{
	int i, j, k, B, C;
	double p;

	if (fgot[r][A] == id) return ftab[r][A];
	fgot[r][A] = id;
	ftab[r][A] = 0.;

	if (r == n) return ftab[r][A] = (((A >> (m - 1)) & 1) ? 1. : 0.);
	if (A == 0) return ftab[r][A] = 0.;

	/* check all possible 2^m arrangements of blocks on r-th row */
	for (B = 0; B < (1 << m); B++) {
		/* compute the probability of generating such an arrangement */
		p = 1.;
		for (i = 0; i < m; i++)
			p *= (B & (1 << i)) ? P[r][i] : (1. - P[r][i]);
		if (p < EPS) continue;

		for (C = 0, i = 0; i < m; i++) {
			if (B & (1 << i)) continue;

			for (j = i; j < m && ((B >> j) & 1) == 0; j++)
				if ((A >> j) & 1) { C |= 1 << i; break; }

			for (j = i; j >= 0 && ((B >> j) & 1) == 0; j--)
				if ((A >> j) & 1) { C |= 1 << i; break; }
		}

		ftab[r][A] += p * f(r+1, C);
	}

	return ftab[r][A];
}

void solve()
{

	id++;
	printf("%.5f\n", f(0,1));

}

int main()
{
	int i, j, t;

	id = 42;
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		assert(1 <= n && n <= 5 && 1 <= m && m <= 6);

		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				scanf("%lf", &P[i][j]);

		solve();

		if (t) printf("\n");
	}

	return 0;
}
