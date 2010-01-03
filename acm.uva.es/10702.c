#include <stdio.h>
#include <string.h>

int d[128][128], e[128], n, s, t;

int solve()
{
	static int buf1[128], buf2[128];
	int i, j, *p, *next;

	for (p = buf1, i = 1; i <= n; i++)
		p[i] = -1;
	p[s] = 0;

	while (t-- > 0) {
		next = (p == buf1) ? buf2 : buf1;
		for (i = 1; i <= n; i++) {
			next[i] = -1;
			for (j = 1; j <= n; j++)
				if (p[j] >= 0 && i != j &&
				    (p[j] + d[j][i]) > next[i])
					next[i] = p[j] + d[j][i];
		}
		p = next;
	}

	for (j = 0, i = 1; i <= n; i++)
		if (e[i] && p[i] > j) j = p[i];

	return j;
}

int main()
{
	int i, j, en, x;

	while (scanf("%d %d %d %d", &n, &s, &en, &t) == 4 && n > 0) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				scanf("%d", &d[i][j]);

		memset(e, 0, sizeof(e));
		while (en-- > 0 && scanf("%d", &x) == 1)
			e[x] = 1;

		printf("%d\n", solve());
	}

	return 0;
}
