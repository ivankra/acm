#include <stdio.h>
#include <string.h>

int adj[128][128], n, s, t;

int find()
{
	static int q[128], pred[128], lim[128], qh, qt;
	int r, i, k;

	for (r = 0;;) {
		memset(pred, '\0', sizeof(pred));

		q[0] = s;
		lim[s] = 1000;
		pred[s] = s;
		qh = 0;
		qt = 1;

		for (; qh < qt && q[qh] != t; qh++) {
			k = q[qh];

			for (i = 1; i <= n; i++) {
				if (pred[i] || adj[k][i] <= 0)
					continue;

				pred[i] = k;
				lim[i] = (adj[k][i] < lim[k]) ? adj[k][i] : lim[k];

				q[qt++] = i;
			}
		}

		if (qh >= qt)
			break;

		k = lim[t];
		for (i = t; i != s; i = pred[i]) {
			adj[pred[i]][i] -= k;
			adj[i][pred[i]] += k;
		}

		r += k;
	}

	return r;
}

int main()
{
	int w, c, x, y, z;

	for (w = 1; scanf("%d %d %d %d", &n, &s, &t, &c) == 4 && n > 0; w++) {
		memset(adj, '\0', sizeof(adj));

		while (c-- > 0 && scanf("%d %d %d", &x, &y, &z) == 3) {
			if (x == y) continue;
			adj[x][y] += z;
			adj[y][x] += z;
		}

		printf("Network %d\nThe bandwidth is %d.\n\n", w, find());
	}

	return 0;
}
