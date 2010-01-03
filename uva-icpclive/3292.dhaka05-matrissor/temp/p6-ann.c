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

int tr_what[64][64], tr_arg[64][64];

void trace(int s, int m, int jflag)
{
	int i;

	/* tr_what = '?' (error), 'i' (immediate), 'j' (join), 's' (split) */

	if (tr_what[s][m] == 'i') {
		printf("(");
		for (i = 0; i < m; i++)
			printf(i ? ", %dx%d" : "%dx%d", R[s+i], R[s+i+1]);
		printf(")");
		return;
	}

	if (tr_what[s][m] == 's') {
		printf("(");
		trace(s, tr_arg[s][m], 0);
		printf(", ");
		trace(s + tr_arg[s][m], m - tr_arg[s][m], 0);
		printf(")");
		return;
	}

	if (tr_what[s][m] == 'j') {
		trace(s, tr_arg[s][m], 0);
		printf("#");
		printf(", ");
		trace(s + tr_arg[s][m], m - tr_arg[s][m], 0);
		printf(")");
		return;
	}

	printf("?");
}

static int f(int s, int m)
{
	int p, i, j, k;

	if (fgot[s][m] == ID) return ftab[s][m];
	fgot[s][m] = ID;

	tr_what[s][m] = '?';

	ftab[s][m] = INF;
	ctab[s][m] = INF;

	if (m <= 1) {
		tr_what[s][m] = 'i';
		ctab[s][m] = 0;
		return ftab[s][m] = 0;
	}

	if (cost[s][m] <= cap) {
		tr_what[s][m] = 'i';
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

{int X;
		if (ftab[s][p] > 0 && (ctab[s][p] + k) <= cap)
X='j',			k += ctab[s][p];
		else
X='s',			i++;

		if (i < ftab[s][m] || (i == ftab[s][m] && k < ctab[s][m])) {
			ftab[s][m] = i;
			ctab[s][m] = k;
tr_what[s][m] = X;
tr_arg[s][m] = p;
		}
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
			else {
				printf("%d", f(0, n));
#if 1
				printf("   "); trace(0, n, 0);
#endif
				printf("\n");
			}
		}

		printf("\n");
	}

	exit(0);
}
