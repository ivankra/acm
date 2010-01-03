#include <cstdio>
#include <cstring>
#include <cstdlib>

int G[16][16], n;
int memo[65536], got[65536], got_id;

int f(int x, int w)
{
	if (got[w] == got_id) return memo[w];
	got[w] = got_id;

	memo[w] = 1<<30;
	for (int y = 0; y < n; y++)
		if (w & (1 << y))
			memo[w] <?= G[x][y] + f(x+1, w ^ (1 << y));
	return memo[w];
}

// min cost bipartite matching
// O(n 2^n) algorithm
int match()
{
	got[0] = ++got_id;
	memo[0] = 0;
	return f(0, (1<<n)-1);
}

int main()
{
	int x[16], y[16];
	memset(got, 0, sizeof(got));
	got_id = 42;
	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		for (int i = 0; i < n; i++) scanf("%d %d", &x[i], &y[i]);

		int ret = 1<<30;
		for (int r = 1; r <= n; r++) {
			// row r
			for (int i = 0; i < n; i++) {
				int y0 = r, x0 = i+1;
				for (int j = 0; j < n; j++)
					G[i][j] = abs(x0-x[j]) + abs(y0-y[j]);
			}
			ret <?= match();

			// column r
			for (int i = 0; i < n; i++) {
				int y0 = i+1, x0 = r;
				for (int j = 0; j < n; j++)
					G[i][j] = abs(x0-x[j]) + abs(y0-y[j]);
			}
			ret <?= match();
		}

		// main diagonal
		for (int i = 0, y0 = 1, x0 = 1; i < n; y0++, x0++, i++)
			for (int j = 0; j < n; j++)
				G[i][j] = abs(x0-x[j]) + abs(y0-y[j]);
		ret <?= match();

		// side diagonal
		for (int i = 0, y0 = 1, x0 = n; i < n; y0++, x0--, i++)
			for (int j = 0; j < n; j++)
				G[i][j] = abs(x0-x[j]) + abs(y0-y[j]);
		ret <?= match();

		printf("Board %d: %d moves required.\n\n", cs, ret);
	}
	return 0;
}
