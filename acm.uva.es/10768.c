#include <stdio.h>
#include <string.h>

static int adj[32][32], n;

static int k5()
{
	static int p[8];
	int i, k;

	for (p[0] = 0, k = 0; k >= 0;) {
		if (++p[k] > n) {
			k--;
			continue;
		}

		for (i = 0; i < k; i++)
			if (!adj[p[k]][p[i]]) break;

		if (i < k) {
			k--;
			continue;
		}

		if (k == 4)
			return 1;

		p[k + 1] = p[k];
		k++;
	}

	return 0;
}

static int k33()
{
/*
   a     b     c
   | \ / | \ / |
   d     e     f
*/
	int a, b, c, d, e, f;

for (a = 1; a <= n; a++) {
  for (d = 1; d <= n; d++) {
    if (!adj[a][d]) continue;
    for (b = 1; b <= n; b++) {
      if (!adj[b][d] || a == b) continue;
      for (e = 1; e <= n; e++) {
        if (!adj[a][e] || !adj[b][e] || d == e) continue;
        for (c = 1; c <= n; c++) {
          if (!adj[d][c] || !adj[e][c] || c == a || c == b) continue;
          for (f = 1; f <= n; f++) {
            if (!adj[a][f] || !adj[b][f] || !adj[c][f] || f == d || f == e)
              continue;
            return 1;
          }
        }
      }
    }
  }
}

	return 0;
}

int main()
{
	static int deg[32], m, x, y;
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		memset(adj, '\0', sizeof(adj));
		memset(deg, '\0', sizeof(deg));

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
			if (x != y) adj[x][y] = adj[y][x] = 1;

		for (i = 1; i <= n; i++)
			for (deg[i] = 0, j = 1; j <= n; j++)
				deg[i] += adj[i][j];

		do {
			for (i = 1, j = 0; i <= n; i++) {
				if (deg[i] == 1) {
					for (deg[i] = 0, j = 1; j <= n; j++)
						if (adj[i][j]) break;
					adj[i][j] = adj[j][i] = 0;
					deg[j]--;
				} else if (deg[i] == 2) {
					for (deg[i] = 0, j = 1; j <= n; j++)
						if (adj[i][j]) break;

					for (k = j + 1; k <= n; k++)
						if (adj[i][k]) break;

					adj[i][j] = adj[j][i] = 0;
					adj[i][k] = adj[k][i] = 0;
					adj[j][k] = adj[k][j] = 1;
				}
			}
		} while (j != 0);

		for (i = 1; i <= n; i++) {
			if (deg[i] == 0) continue;
			for (j = 1, k = 1; j <= n; j++)
				if (deg[j] != 0) adj[i][k++] = adj[i][j];
		}

		for (i = 1, k = 0; i <= n; i++) {
			if (deg[i] == 0)
				continue;

			if (i != ++k)
				memcpy(adj[k], adj[i], sizeof(adj[0]));
		}

		n = k;

		for (i = 1; i <= n; i++)
			adj[i][i] = 0;

		printf((k5() || k33()) ? "NO\n" : "YES\n");
	}

	return 0;
}
