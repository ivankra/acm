#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NINF -0x3FFFFFFF

int a[128][128], n;
int got[6][128][128], tab[6][128][128];

int f(int k, int r, int c)
{
	int i, j, m, s;

	if (got[k][r][c]) return tab[k][r][c];
	got[k][r][c] = 1;
	tab[k][r][c] = NINF;

	if (r == n) {
		for (s = 0, m = k, i = c; i <= n; i++) {
			if (a[r][i] < 0 && m-- == 0) break;
			s += a[r][i];
		}
		if (m < 0) s = NINF;
		return tab[k][r][c] = s;
	}

	for (s = 0, m = k, i = c; i <= n; i++) {
		if (a[r][i] < 0 && m-- == 0) break;
		s += a[r][i];

		j = f(m, r + 1, i);
		if (j > NINF && (j + s) > tab[k][r][c]) tab[k][r][c] = j + s;
	}

	for (s = 0, m = k, i = c; i >= 1; i--) {
		if (a[r][i] < 0 && m-- == 0) break;
		s += a[r][i];

		j = f(m, r + 1, i);
		if (j > NINF && (j + s) > tab[k][r][c]) tab[k][r][c] = j + s;
	}

	return tab[k][r][c];
}

int main()
{
	int i, j, k, t;

	for (t = 1; scanf("%d %d", &n, &k) == 2 && n > 0; t++) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);

		if (k < 0) k = 0;
		assert(k <= 5);

		memset(got, 0, sizeof(got));

		i = f(k, 1, 1);
		if (i == NINF)
			printf("Case %d: impossible\n", t);
		else
			printf("Case %d: %d\n", t, i);
	}

	return 0;
}
