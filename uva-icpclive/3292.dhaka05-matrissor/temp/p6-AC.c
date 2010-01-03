/* approach:
   along with computing f(i,j), keep number of operations performed
   at the last step of f(i,j)'s optimal sequence, and when possible
   join sequence ((a,b),c) into (a,b,c) thus saving one matrissor's use.

   not sure if that's always correct, though
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF 0x1FFFFFFF

int R[64], cost[64][64], cap, n;
int ftab[64][64], ctab[64][64], fgot[64][64];

/* R[i] = no. of rows in matrix #i (i=0..n-1); R[n] = no. of columns in last matrix */
/* cost[i][k] = cost of multiplying matrices i..i+(k-1) sequentially;
   the resulting matrix has dimensions R[i] x R[i+k] */

int f(int s, int m)
{
	int p, q, i, j, k;

	assert((s + m) <= n);

	if (fgot[s][m]) return ftab[s][m];
	fgot[s][m] = 1;

	ftab[s][m] = INF;
	ctab[s][m] = INF;

	if (m <= 1) {
		ctab[s][m] = 0;
		return ftab[s][m] = 0;
	}

	if (cost[s][m] <= cap) {
		ctab[s][m] = cost[s][m];
		return ftab[s][m] = 1;
	}

/* split into two parts of lengths: p, m-p
               matrices: s..s+p-1, s+p..s+m-1
                   cost: R[s] (R[s+p] R[s+m])
*/
	for (p = 1; p < m; p++) {
		k = R[s] * R[s + p] * R[s + m];
		if (k > cap) continue;

		i = f(s, p);
		if (i == INF) continue;

		j = f(s + p, m - p);
		if (j == INF) continue;

		i += j;

		if (ftab[s][p] > 0 && (ctab[s][p] + k) <= cap) {
/*printf("s=%d m=%d: p=%d k=%d; ctab[s][p]=%d +k=%d *** i=%d\n", s,m,p,k,ctab[s][p],ctab[s][p]+k,i);*/
			k += ctab[s][p];
		} else {
/*printf("s=%d m=%d: p=%d k=%d; ctab[s][p]=%d +k=%d\n", s,m,p,k,ctab[s][p],ctab[s][p]+k);*/
			i++;
		}

		if (i < ftab[s][m] || (i == ftab[s][m] && k < ctab[s][m])) {
			ftab[s][m] = i;
			ctab[s][m] = k;
/*printf("s=%d m=%d: f=%d c=%d\n", s,m,i,k);*/
		}
	}

/*printf("f(s=%d,m=%d)=%d  c=%d\n", s,m,ftab[s][m], ctab[s][m]);*/

	return ftab[s][m];
}

void mkcost()
{
	int i, k;

	memset(cost, 0, sizeof(cost));
	for (k = 2; k <= n; k++)
		for (i = 0; (i + k) <= n; i++)
			cost[i][k] = cost[i][k-1] + R[i] * R[i+k-1] * R[i+k];
}

int main()
{
	int rows[64], cols[64], i, q, t, T;

	for (scanf("%d", &T), t = 1; t <= T && scanf("%d", &n) == 1; t++) {
		assert(2 <= n && n <= 50);

		for (i = 0; i < n; i++) {
			scanf("%d %d", &rows[i], &cols[i]);
			assert(1 <= rows[i] && rows[i] <= 50);
			assert(1 <= cols[i] && cols[i] <= 50);
			if (i >= 1) assert(cols[i - 1] == rows[i]);
			R[i] = rows[i];
		}
		R[n] = cols[n - 1];

		printf("Matrix #%d\n", t);

		mkcost();

		for (scanf("%d", &q); q-- > 0 && scanf("%d", &cap) == 1;) {
			assert(0 <= cap && cap <= 1000000000);

			memset(fgot, 0, sizeof(fgot));

			if (f(0, n) == INF)
				printf("Impossible.\n");
			else
				printf("%d\n", f(0, n));
		}

		printf("\n");
	}

	return 0;
}
