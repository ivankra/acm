#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int adj[8][8][128], cnt[8][8], deg[8], use[128], ex[128], ey[128], n;
int lv[128], le[128], ln;

void go(int s)
{
	int b, e, v;

	for (b = ln, e = 0;;) {
		for (v = 0; v <= 6; v++) {
			while (cnt[s][v] > 0) {
				e = adj[s][v][cnt[s][v] - 1];
				if (use[abs(e)]) cnt[s][v]--; else break;
			}
			if (cnt[s][v] > 0) break;
		}

		if (v < 0 || v > 6)
			break;

		cnt[s][v]--;
		use[abs(e)] = 1;

		lv[ln] = s;
		le[ln++] = e;

		s = v;
	}

	while (ln > b) {
		ln--;
		printf("%d %c\n", abs(le[ln]), (le[ln] < 0) ? '+' : '-');
		s = lv[ln];
		go(s);
	}
}

int solve()
{
	int f[8][8], i, j, k, s, t;

	for (i = 0, j = 0; i <= 6; i++)
		if ((deg[i] % 2) != 0) j++;
	if (j != 0 && j != 2) return 0;

	if (j == 0) {
		for (s = 0; s <= 6 && deg[s] == 0; s++);
		t = s;
	} else {
		for (s = 0; s <= 6 && (deg[s] % 2) == 0; s++);
		for (t = s + 1; t <= 6 && (deg[t] % 2) == 0; t++);
	}

	for (i = 0; i <= 6; i++)
		for (j = 0; j <= 6; j++)
			f[i][j] = (cnt[i][j] > 0) ? 1 : 0;

	for (k = 0; k <= 6; k++)
		for (i = 0; i <= 6; i++)
			for (j = 0; j <= 6; j++)
				f[i][j] |= f[i][k] & f[k][j];

	for (i = 0; i <= 6; i++)
		for (j = 0; j <= 6; j++)
			if (deg[i] > 0 && deg[j] > 0 && f[i][j] == 0) return 0;

	go(s);

	return 1;
}

int main()
{
	int x, y, i;

	memset(cnt, 0, sizeof(cnt));
	memset(deg, 0, sizeof(deg));
	memset(use, 0, sizeof(use));
	memset(adj, 0, sizeof(adj));

	scanf("%d", &n);
	assert(1 <= n && n < 128);

	for (i = 1; i <= n && scanf("%d %d", &x, &y) == 2; i++) {
		ex[i] = x; ey[i] = y;
		adj[x][y][cnt[x][y]++] = i;
		adj[y][x][cnt[y][x]++] = -i;
		deg[x]++; deg[y]++;
	}

	if (!solve())
		printf("No solution\n");

	return 0;
}
