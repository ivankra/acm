/*
ID: infnty1
PROB: fence
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int adj[512][512], tour[1024], n;

void find(int x)
{
	for (int y = 1; adj[0][x] > 0 && y <= 500;) {
		if (adj[x][y] == 0) { y++; continue; }
		adj[x][y]--; adj[y][x]--; adj[0][x]--; adj[0][y]--;
		find(y);
	}
	tour[n++] = x;
}

int main()
{
	int m, x, y;

	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);

	memset(adj, 0, sizeof(adj));
	for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x, &y) == 2;)
		adj[x][y]++, adj[y][x]++, adj[0][x]++, adj[0][y]++;

	for (x = 1; x <= 500 && (adj[0][x] & 1) == 0; x++);
	if (x > 500) for (x = 1; x <= 500 && adj[0][x] == 0; x++);

	n = 0;
	if (x <= 500) find(x);

	while (n--) printf("%d\n", tour[n]);

	return 0;
}
