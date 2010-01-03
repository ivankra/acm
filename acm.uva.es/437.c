#include <stdio.h>

struct {
	int x1, x2, h;
} vert[256];

int adj[256][256], n;

void add(int x1, int x2, int h)
{
	int i;

	if (x1 > x2) {
		i = x1;
		x1 = x2;
		x2 = i;
	}

	for (i = 1; i <= n; i++)
		if (vert[i].x1 == x1 && vert[i].x2 == x2) return;

	n++;
	vert[n].x1 = x1;
	vert[n].x2 = x2;
	vert[n].h = h;
}

int find()
{
	int i, j, k;

	for (adj[0][0] = 0, i = 1; i <= n; i++)
		adj[0][i] = vert[i].h;

	for (i = 1; i <= n; i++) {
		adj[i][0] = 0;
		for (j = 1; j <= n; j++) {
			if (vert[j].x1 < vert[i].x1 && vert[j].x2 < vert[i].x2)
				adj[i][j] = vert[j].h;
			else
				adj[i][j] = 0;
		}
	}

	for (k = 1; k <= n; k++) {
		for (i = 0; i <= n; i++) {
			if (adj[i][k] == 0)
				continue;

			for (j = 0; j <= n; j++) {
				if (adj[k][j] == 0)
					continue;

				if ((adj[i][k] + adj[k][j]) <= adj[i][j])
					continue;

				adj[i][j] = adj[i][k] + adj[k][j];
			}
		}
	}

	for (k = 0, i = 1; i <= n; i++)
		if (adj[0][i] > k) k = adj[0][i];

	return k;
}

int main()
{
	int t, r, x, y, z;

	for (t = 1; scanf("%d", &r) == 1 && r > 0; t++) {
		for (n = 0; r-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3;) {
			add(x, y, z);
			add(x, z, y);
			add(y, z, x);
		}

		printf("Case %d: maximum height = %d\n", t, find());
	}

	return 0;
}
