#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

#define NOPATH 0xFFFFFF

static char adj[676][676], names[676][4];
static int present[676], src, dest;

static void solve()
{
	static int dist[676], visited[676], pred[676], succ[676];
	int i, k;

	for (i = 0; i < 676; i++) {
		dist[i] = NOPATH;
		visited[i] = 0;
		pred[i] = -1;
	}
	dist[src] = 0;

	for (;;) {
		for (i = 0; i < 676; i++)
			if (present[i] && visited[i] == 0 &&
			     dist[i] != NOPATH)
				break;

		if (i >= 676)
			break;

		for (k = i++; i < 676; i++)
			if (present[i] && !visited[i] && dist[i] < dist[k])
				k = i;

		visited[k] = 1;

		for (i = 0; i < 676; i++)
			if (adj[k][i] && dist[i] > (dist[k] + 1)) {
				dist[i] = dist[k] + 1;
				pred[i] = k;
			}
	}

	if (dist[dest] == NOPATH) {
		printf("No route\n");
		return;
	}

	for (i = dest, succ[dest] = -1; pred[i] >= 0; i = pred[i])
		succ[pred[i]] = i;

	for (i = src; succ[i] >= 0; i = succ[i])
		printf("%s %s\n", names[i], names[succ[i]]);
}

int main()
{
	int i, n, t;
	char a[16], b[16];

	for (i = 0; i < 676; i++)
		sprintf(names[i], "%c%c", (i / 26) + 'A', (i % 26) + 'A');

	for (t = 0; scanf("%d", &n) == 1; t++) {
		memset(adj, '\0', sizeof(adj));

		for (i = 0; scanf(" %[A-Za-z] %[A-Za-z]", a, b) == 2; i++) {
			src = (toupper(a[0])-'A') * 26 + toupper(a[1]) - 'A';
			dest = (toupper(b[0])-'A') * 26 + toupper(b[1]) - 'A';

			present[src] = present[dest] = 1;

			if (i >= n)
				break;

			adj[src][dest] = adj[dest][src] = 1;
		}
			

		if (t != 0)
			printf("\n");

		solve();
	}	

	return 0;
}
