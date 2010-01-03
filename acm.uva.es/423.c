#include <stdio.h>

#define MAXPATH 0x7FFFFFFF

static int adj[128][128], nodes[128], visited[128], n;

int main()
{
	register int i, j, k, c;

	for (nodes[0] = 0, i = 1; i < 128; i++) nodes[i] = MAXPATH;
	for (i = 0; i < 128; i++) visited[i] = 0;
	for (i = 0; i < 128; i++)
		for (j = 0; j < 128; j++) adj[i][j] = MAXPATH;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		adj[i][i] = 0;
		for (j = 0; j < i; j++) {
			while ((c = getchar()) != EOF && c != 'x' && 
			       (c < '0' || c > '9'));

			if (c >= '0' && c <= '9') {
				for (k = 0; c >= '0' && c <= '9'; c = getchar())
					k = k * 10 + c - '0';
				if (c != EOF) ungetc(c, stdin);
			} else {
				k = MAXPATH;
			}

			adj[i][j] = k;
			adj[j][i] = k;
		}
	}

	for (;;) {
		for (k = -1, i = 0; i < n; i++)
			if (!visited[i] && (k < 0 || nodes[i] < nodes[k])) k=i;

		if (k < 0)
			break;

		for (visited[k] = 1, i = 0; i < n; i++) {
			if (i == k || adj[i][k] == MAXPATH) continue;
			if (nodes[i] > (j = nodes[k] + adj[k][i]))
				nodes[i] = j;
		}
	}

	for (i = 0, k = 0; i < n; i++)
		if (nodes[i] > k) k = nodes[i];

	printf("%d\n", k);

	return 0;
}
