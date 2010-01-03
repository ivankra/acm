#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 128

int cost[N][N], adj[N][N], tax[N], pred[N], dist[N], v[N], path[N], n, t, a, b;
char buf[16384];

int main()
{
	int i, j, k;
	char *p;

	for (scanf("%d\n", &t); t-- > 0;) {
		if (gets(buf) == NULL) break;

		for (n = 0, p = buf;;) {
			while (*p && !isdigit(*p)) p++;
			if (*p == '\0') break;
			n++;
			while (*p && isdigit(*p)) p++;
		}

		if (n == 0)
			continue;

		for (i = 0; i <= n;) {
			for (j = 0, p = buf; j < n; j++) {
				for (; *p && *p != '-' && !isdigit(*p); p++);
				cost[i][j] = -1;
				sscanf(p, "%d", &cost[i][j]);
				while (*p && (*p == '-' || isdigit(*p))) p++;
			}

			if (++i <= n) {
				memset(buf, '\0', sizeof(buf));
				gets(buf);
			}
		}

		for (i = 0; i < n; i++)
			tax[i] = cost[n][i];

		while (gets(buf) && sscanf(buf, "%d%d", &a, &b) == 2) {
			for (a--, b--, i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					adj[i][j] = cost[i][j];

			for (i = 0; i < n; i++) {
				if (i == a) continue;
				for (j = 0; j < n; j++)
					if (adj[i][j] >= 0)
						adj[i][j] += tax[i];
			}

			printf("From %d to %d :\n", a+1, b+1);

			for (i = 0; i < n; i++)
				dist[i] = -1, v[i] = 0, pred[i] = i;
			dist[a] = 0;
			pred[a] = a;

			for (;;) {
				for (k = 0; k < n && (v[k] || dist[k]<0); k++);
				if (k >= n)
					break;

				for (i = k + 1; i < n; i++)
					if (v[i] == 0 && (dist[i] >= 0 &&
							  dist[i] < dist[k]))
						k = i;

				if (dist[k] < 0)
					break;
				v[k] = 1;

				for (i = 0; i < n; i++) {
					if (adj[k][i] < 0)
						continue;

					j = dist[k] + adj[k][i];
					if (dist[i] < 0 || dist[i] > j) {
						dist[i] = j;
						pred[i] = k;
					}
				}
			}

			for (i = b, j = 0; pred[i] != i; i = pred[i])
				path[j++] = i;

			printf("Path: %d", a+1);
			while (j-- > 0)
				printf("-->%d", path[j]+1);

			printf("\nTotal cost : %d\n", dist[b]);
			if (t != 0) printf("\n");
		}
	}

	return 0;
}
