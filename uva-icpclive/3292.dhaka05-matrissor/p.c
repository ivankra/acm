/* approach:
   along with computing f(i,j), keep number of operations performed
   at the last step of f(i,j)'s optimal sequence, and when possible
   join sequence ((a,b),c) into (a,b,c) thus saving one matrissor's use.

   not sure if that's always correct, though
 */
#include <stdio.h>
#include <string.h>

#define INF 0x1FFFFFFF

static int R[64], cost[64][64], cap, n;
static int ftab[64][64], ctab[64][64], fgot[64][64], ID=42;

static int f(int s, int m)
{
	int p, i, j, k;

	if (fgot[s][m] == ID) return ftab[s][m];
	fgot[s][m] = ID;

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

	for (p = 1; p < m; p++) {
		k = R[s] * R[s + p] * R[s + m];
		if (k > cap) continue;

		i = f(s, p);
		if (i == INF) continue;

		j = f(s + p, m - p);
		if (j == INF) continue;

		i += j;

		if (ftab[s][p] > 0 && (ctab[s][p] + k) <= cap)
			k += ctab[s][p];
		else
			i++;

		if (i < ftab[s][m] || (i == ftab[s][m] && k < ctab[s][m])) {
			ftab[s][m] = i;
			ctab[s][m] = k;
		}
	}

	return ftab[s][m];
}

static void mkcost()
{
	int i, k;

	memset(cost, 0, sizeof(cost));
	for (k = 2; k <= n; k++)
		for (i = 0; (i + k) <= n; i++)
			cost[i][k] = cost[i][k-1] + R[i] * R[i+k-1] * R[i+k];
}

int main()
{
	static int rows[64], cols[64], q, t, T;
	int i;

	for (scanf("%d", &T), t = 1; t <= T && scanf("%d", &n) == 1; t++) {
		for (i = 0; i < n; i++) {
			scanf("%d %d", &rows[i], &cols[i]);
			R[i] = rows[i];
		}
		R[n] = cols[n - 1];

		printf("Matrix #%d\n", t);

		mkcost();

		for (scanf("%d", &q); q-- > 0 && scanf("%d", &cap) == 1;) {
			ID++;

			if (f(0, n) == INF)
				printf("Impossible.\n");
			else
				printf("%d\n", f(0, n));
		}

		printf("\n");
	}

	exit(0);
}
