#include <stdio.h>

char wa[128][128], wb[128][128], s[128];
int wr[128], n, k, p, x, t;

int test(int c, int d)
{
	int i, j;

	for (i = 0; i < k; i++) {
		j = (wa[i][c] ? -d : 0) + (wb[i][c] ? d : 0);
		if (j != wr[i]) return 0;
	}

	return 1;
}

int main()
{
	int i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &k) == 2;) {
		for (i = 0; i < k && scanf("%d", &p); i++) {
			for (j = 1; j <= n; j++)
				wa[i][j] = wb[i][j] = 0;

			for (j = 0; j < p && scanf("%d", &x) == 1; j++)
				wa[i][x] = 1;

			for (j = 0; j < p && scanf("%d", &x) == 1; j++)
				wb[i][x] = 1;

			scanf(" %s", s);
			if (s[0] == '<')
				wr[i] = -1;
			else if (s[0] == '>')
				wr[i] = 1;
			else
				wr[i] = 0;
		}

		for (i = 1; i <= n; i++)
			if (test(i, 1) || test(i, -1)) break;

		if (i <= n) {
			for (j = i + 1; j <= n; j++)
				if (test(j, 1) || test(j, -1)) break;
			if (j <= n) i = n + 1;
		}

		printf(t ? "%d\n\n" : "%d\n", (i <= n) ? i : 0);
	}

	return 0;
}
