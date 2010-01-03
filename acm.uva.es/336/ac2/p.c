#include <stdio.h>

int main()
{
	static int d[32][32], map[32], t, m, n, a, b;
	register int i, j, k;

	for (t = 1; scanf("%d", &m) == 1 && m > 0;) {
		for (i = 0; i < 32; i++) {
			for (j = 0; j < 32; j++)
				d[i][j] = 0xFFFF;
			d[i][i] = 0;
		}

		for (n = 0; m-- > 0 && scanf("%d %d", &a, &b) == 2;) {
			for (i = 0; i < n && map[i] != a; i++);

			if (i == n) {
				map[n] = a;
				a = n++;
			} else {
				a = i;
			}

			for (i = 0; i < n && map[i] != b; i++);

			if (i == n) {
				map[n] = b;
				b = n++;
			} else {
				b = i;
			}

			if (a != b)
				d[a][b] = d[b][a] = 1;
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (d[i][k] > 256 || i == k) continue;
				for (j = 0; j < i; j++) {
					if (d[i][j] > (d[i][k] + d[k][j]))
						d[j][i] = d[i][j] =
							d[i][k] + d[k][j];
				}
			}
		}

		for (; scanf("%d %d", &a, &b) == 2; t++) {
			if (a == 0 && b == 0)
				break;

			if (b < 0) b = 0;

			for (j = 0; j < n && map[j] != a; j++);

			for (i = 0, k = 0; i < n; i++)
				if (d[j][i] > b) k++;

			printf("Case %d: %d nodes not reachable from "
			       "node %d with TTL = %d.\n",
			       t, k, a, b);
		}
	}

	return 0;
}
