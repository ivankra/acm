#include <cstdio>
#include <cstdlib>
#include <cstring>
#define INF 0x1fffffff

int memo[11][1<<11], d[16][16], n;

int f(int s, int a)
{
	if (memo[s][a] >= 0) return memo[s][a];
	if (a == 1) return memo[s][a] = d[s][0];

	memo[s][a] = INF;
	for (int t = 1; t < n; t++)
		if (a & (1 << t))
			memo[s][a] <?= d[s][t] + f(t, a ^ (1 << t));

	return memo[s][a];
}

int main()
{
	struct { int x, y; } V[16];
	int i, j, T;

	for (scanf("%d", &T); T-- > 0;) {
		scanf("%*d %*d %d %d %d", &V[0].x, &V[0].y, &n);
		for (n++, i = 1; i < n; i++)
			scanf("%d %d", &V[i].x, &V[i].y);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				d[i][j] = abs(V[i].x-V[j].x)+abs(V[i].y-V[j].y);

		memset(memo, 0xff, sizeof(memo));
		printf("The shortest path has length %d\n", f(0, (1<<n)-1));
	}

	return 0;
}
