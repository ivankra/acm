#include <stdio.h>
#include <string.h>

static char map[102][128];
static int pred[16384], count[16384], n, m;

static void solve()
{
	register int k, a, b;
	int i, j;

	for (a = 0; a < n; a++) {
		for (k = (a << 7), b = 0; b < m; b++, k++) {
			pred[k] = k;
			count[k] = 1;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (map[i][j] != 'W')
				continue;

			k = (i << 7) + j;

			for (a = k; pred[a] != a; a = pred[a]);
			pred[k] = a;

#define UNION(by, bx) { \
        k = ((by) << 7) + (bx); \
        for (b = k; pred[b] != b; b = pred[b]); \
	pred[k] = b; \
	if (a != b) { \
		if (count[a] > count[b]) { \
			count[a] += count[b]; \
			pred[b] = a; \
		} else { \
			count[b] += count[a]; \
			a = pred[a] = b; \
		} \
	} \
}

			if (i > 0) {
				if (j > 0 && map[i - 1][j - 1] == 'W')
					UNION(i - 1, j - 1);

				if (map[i - 1][j] == 'W')
					UNION(i - 1, j);

				if ((j + 1) < m && map[i - 1][j + 1] == 'W')
					UNION(i - 1, j + 1);
			}

			if (j > 0 && map[i][j - 1] == 'W') {
				UNION(i, j - 1);
			}
		}
	}
}

int main()
{
	static int t, y, x;
	register int i;

	for (scanf("%d", &t); t-- > 0;) {
		memset(map, '\0', sizeof(map));

		for (n = 0; scanf(" %[LW]", map[n]) == 1; n++);
		for (m = 0; map[0][m]; m++);

		solve();

		while (scanf("%d %d", &y, &x) == 2) {
			if (y <= 0 || x <= 0 || map[y - 1][x - 1] != 'W') {
				printf("0\n");
				continue;
			}

			for (i=((y-1)<<7) + (x-1); pred[i] != i; i = pred[i]);

			printf("%d\n", count[i]);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
