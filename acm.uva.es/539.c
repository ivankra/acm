#include <stdio.h>
#include <string.h>

int adj[32][32], adjy[32][32], deg[32], n, m;
int ex[32], ey[32], eu[32], longest;

void find(int len, int x)
{
	int i;

	if (len > longest)
		longest = len;

	for (i = 0; i < deg[x]; i++) {
		if (eu[adj[x][i]] == 0) {
			eu[adj[x][i]] = 1;
			find(len + 1, adjy[x][i]);
			eu[adj[x][i]] = 0;
		}
	}
}

int main()
{
	int i, m;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		memset(deg, 0, sizeof(deg));
		memset(eu, 0, sizeof(eu));

		for (i = 0; i < m && scanf("%d %d", &ex[i], &ey[i]) == 2; i++) {
			adj[ex[i]][deg[ex[i]]] = i;
			adjy[ex[i]][deg[ex[i]]++] = ey[i];
			adj[ey[i]][deg[ey[i]]] = i;
			adjy[ey[i]][deg[ey[i]]++] = ex[i];
		}

		for (longest = 0, i = 0; i < n; i++)
			find(0, i);

		printf("%d\n", longest);
	}

	return 0;
}
