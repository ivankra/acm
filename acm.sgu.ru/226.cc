#include <stdio.h>
#include <string.h>

#define MAXM 65536

int next[MAXM], col[MAXM], ref[MAXM], last, m, n;
int dist[256][4], qx[MAXM], qc[MAXM], qd[MAXM], x, y, c;

int main()
{
	int i, j, h, t;

	scanf("%d %d", &n, &m);
	for (last = n, i = 0; i <= n; i++) next[i] = 0;

	while (m-- > 0 && scanf("%d %d %d", &x, &y, &c) == 3) {
		last++; col[last] = c; ref[last] = y;
		next[last] = next[x]; next[x] = last;
	}

	memset(dist, 0, sizeof(dist));
	for (qx[0] = qd[h = 0] = t = 1, qc[0] = -1; h < t; h++) {
		if ((dist[n][1] | dist[n][2] | dist[n][3]) != 0) break;
		for (i = next[qx[h]]; i != 0; i = next[i]) {
			if (col[i] == qc[h] || dist[ref[i]][col[i]] > 0) continue;
			dist[ref[i]][col[i]] = qd[t] = qd[h] + 1;
			qx[t] = ref[i]; qc[t] = col[i]; t++;
		}
	}

	for (x = 0, i = 1; i <= 3; i++)
		if (dist[n][i] > 0 && (x == 0 || dist[n][i] < x)) x = dist[n][i];
	printf("%d\n", x - 1);

	return 0;
}
