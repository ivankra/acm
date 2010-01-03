#include <stdio.h>
#include <string.h>

unsigned adj[128][4], isolated[128], best_col[4], col[4];
int n, best, got;

static void f(int k)
{
	if (k > n) {
		if (got > best) {
			memcpy(best_col, col, sizeof(col));
			best = got;
		}
		return;
	}

	if (((adj[k][0] & col[0]) | (adj[k][1] & col[1]) |
	     (adj[k][2] & col[2]) | (adj[k][3] & col[3])) == 0) {
		col[k >> 5] |= 1 << (k & 31);
		got++;

		f(k + 1);

		col[k >> 5] ^= 1 << (k & 31);
		got--;
	}

	if (!isolated[k] && (got + n - k) > best)
		f(k + 1);
}

int main()
{
	int i, m, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		memset(adj, 0, sizeof(adj));

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			adj[x][y >> 5] |= 1 << (y & 31);
			adj[y][x >> 5] |= 1 << (x & 31);
		}

		for (i = 1; i <= n; i++)
			isolated[i] = (adj[i][0] | adj[i][1] | adj[i][2] | adj[i][3]) ? 0 : 1;

		memset(col, 0, sizeof(col));
		memset(best_col, 0, sizeof(best_col));
		best = got = 0;

		f(1);

		printf("%d\n", best);
		for (i = 1, m = 0; i <= n; i++)
			if ((best_col[i >> 5] >> (i & 31)) & 1)
				printf(m++ ? " %d" : "%d", i);
		printf("\n");
	}

	return 0;
}
