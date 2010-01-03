#include <stdio.h>

#define INF 0x7FFFFFFF

int dist[65536], vol[3], cap[3], r1, r2, rd;
int heap[65536], loc[65536], n;

void down(int p)
{
	int i, j, d;

	for (d = dist[heap[p]]; (j = (p << 1)) <= n; p = i) {
		i = (dist[heap[j]] < d) ? j : p;
		j++;
		if (j <= n && dist[heap[j]] < dist[heap[i]]) i = j;

		if (i == p) break;

		j = heap[i];
		loc[heap[i] = heap[p]] = i;
		loc[heap[p] = j] = p;
	}
}

void up(int p)
{
	int d, t;

	for (d = dist[t = heap[p]]; p > 1 && dist[heap[p >> 1]] > d; p >>= 1)
		loc[heap[p] = heap[p >> 1]] = p;
	loc[heap[p] = t] = p;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int main()
{
	int i, j, k, u, v, t;

	for (scanf("%d", &t); t-- > 0;) {
		scanf("%d %d %d %d", &cap[0], &cap[1], &cap[2], &rd);

		for (i = 0; i < 65536; i++)
			dist[i] = INF;

		dist[0] = 0;
		r1 = r2 = 0;

		loc[heap[n = 1] = 0] = 1;

		while (n > 0) {
			u = heap[1];
			loc[heap[1] = heap[n--]] = 1;
			if (n > 0) down(1);

			vol[0] = u >> 8;
			vol[1] = u & 0xFF;
			vol[2] = cap[2] - vol[1] - vol[0];

			for (i = j = 0; i < 3; i++)
				if (j < vol[i] && vol[i] <= rd) j = vol[i];

			if (j > r2) {
				r2 = j;
				r1 = dist[u];
				if (r2 == rd) break;
			}

			for (i = 0; i < 3; i++) {
				if (vol[i] == 0) continue;

				for (j = 0; j < 3; j++) {
					if (i == j || vol[j] >= cap[j])
						continue;

					k = min(vol[i], cap[j] - vol[j]);
					vol[i] -= k;
					vol[j] += k;

					v = (vol[0] << 8) | vol[1];
					if (dist[v] > (dist[u] + k)) {
						if (dist[v] == INF) {
							n++;
							loc[heap[n] = v] = n;
						}
						dist[v] = dist[u] + k;
						up(loc[v]);
					}

					vol[i] += k;
					vol[j] -= k;
				}
			}
		}

		printf("%d %d\n", r1, r2);
	}

	return 0;
}
