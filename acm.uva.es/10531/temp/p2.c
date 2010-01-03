#include <stdio.h>
#include <assert.h>

#define EPS 1e-12

int fgot[8][128], enforce_r, enforce_b, id, n, m, tflag;
double P[8][8], R[8][8], ftab[8][128], xtab[8][128];

void transpose()
{
	double T[8][8];
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			T[i][j] = P[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			P[j][i] = T[i][j];

	i = m; m = n; n = i;
}

/* rows are numbered 0,1,...,n-1
   columns: 0,1,...,m-1 */

/* returns the probability of generating a valid maze, provided that
   the rows 0,1,...,r-1 have already been generated, and there's path from
   (0,0) to (r-1,i) if ((A >> i) & 1) == 1.

   enforce_r/enforce_b make this function to use the arrangement enforce_b
   for the row enforce_r.
 */
double f(int r, int A)
{
	int i, j, B, C;
	double p;

	if (fgot[r][A] == id) return ftab[r][A];
	fgot[r][A] = id;
	ftab[r][A] = 0.;

	if (r == n) return ftab[r][A] = (((A >> (m - 1)) & 1) ? 1. : 0.);
	if (A == 0) return ftab[r][A] = 0.;

	if (enforce_r == r) {
		B = enforce_b;
		for (C = 0, i = 0; i < m; i++) {
			if (B & (1 << i)) continue;

			for (j = i; j < m && ((B >> j) & 1) == 0; j++)
				if ((A >> j) & 1) { C |= 1 << i; break; }

			for (j = i; j >= 0 && ((B >> j) & 1) == 0; j--)
				if ((A >> j) & 1) { C |= 1 << i; break; }
		}

		return ftab[r][A] = xtab[r+1][C];
	}

	for (B = 0; B < (1 << m); B++) {
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
	int i, j, r;
	double p;

	tflag = 0;
	if (m > n) {
		transpose();
		tflag = 1;
	}

	enforce_r = 999;
	id++;
	for (i = n; i >= 0; i--)
		for (j = 0; j < (1 << m); j++)
			xtab[i][j] = f(i, j);

	for (r = 0; r < n; r++) {
		for (i = 0; i < m; i++) R[r][i] = 0.;

		enforce_r = r;
		for (enforce_b = 0; enforce_b < (1 << m); enforce_b++) {
			for (p = 1., i = 0; i < m; i++)
				p *= (enforce_b & (1 << i)) ? P[r][i] : (1. - P[r][i]);
			/*if (p < EPS) continue; */

			id++;
			p *= f(0, 1);

			for (i = 0; i < m; i++)
				if (enforce_b & (1 << i)) R[r][i] += p;
		}

		for (i = 0; i < m; i++) R[r][i] /= xtab[0][1];
	}

	if (tflag == 0) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) printf(j ? " %.6f" : "%.6f", R[i][j]);
			printf("\n");
		}
	} else {
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) printf(j ? " %.6f" : "%.6f", R[j][i]);
			printf("\n");
		}
	}
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
