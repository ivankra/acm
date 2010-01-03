#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXPATH 0x7FFFFFFF
#define MAXN 128

int main()
{
	static int m[MAXN][MAXN], n[MAXN], a, b, c;
	static double r;
	register int i, j, k, t;

	for (c = 1; ; c++) {
		for (i = 0; i < MAXN; i++)
			for (j = 0; j < MAXN; j++)
				m[i][j] = (i == j) ? 0 : MAXPATH;
		memset(n, 0, sizeof(n));

		for (i = 0; scanf("%d %d", &a, &b) == 2 && a && b; i++) {
			m[a][b] = 1;
			n[a] = 1;
			n[b] = 1;
		}

		if (i == 0)
			break;

		for (k = 0; k < MAXN; k++) {
			if (n[k] == 0) continue;
			for (i = 0; i < MAXN; i++) {
				if (n[i] == 0 || m[i][k] == MAXPATH) continue;
				for (j = 0; j < MAXN; j++) {
					if (n[j] == 0 || m[k][j] == MAXPATH)
						continue;
					t = m[i][k] + m[k][j];
					if (m[i][j] > t)
						m[i][j] = t;
				}
			}
		}

		for (r = 0., t = 0, i = 0; i < MAXN; i++) {
			if (n[i] == 0) continue;
			for (j = 0; j < MAXN; j++) {
				if (n[j] && i != j) {
					r += m[i][j];
					t++;
				}
			}
		}
		r /= (double)t;

		printf("Case %d: average length between pages = %.3f clicks\n",
		       c, r);
	}

	return 0;
}
