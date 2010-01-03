#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int war[128][128], deg[128], n, m;
int ex[1024], ey[1024], ed[1024], em[1024];
int need[128], seen[128];
vector<int> adj[128];

void tour(int x)
{
	while (adj[x].size() > 0) {
		int y = adj[x].back();
		adj[x].pop_back();
		tour(y);
	}
	printf(m++ ? " %d" : "%d", x);
}

int aug(int x)
{
	if (seen[x]) return 0;
	seen[x] = 1;

	for (int i = 0; i < adj[x].size(); i++) {
		int y = adj[x][i];
		if (em[y] == 0 || aug(em[y])) {
			em[y] = x;
			return 1;
		}
	}

	return 0;
}

int solve()
{
	int i, j, k;

	memset(war, 0, sizeof(war));
	memset(deg, 0, sizeof(deg));
	memset(em, 0, sizeof(em));

	for (i = 1; i <= n; i++)
		adj[i].clear();

	for (i = 0; i < m; i++) {
		war[ex[i]][ey[i]] = war[ey[i]][ex[i]] = 1;
		deg[ex[i]]++; deg[ey[i]]++;
		if (!ed[i]) {
			adj[ex[i]].push_back(i);
			adj[ey[i]].push_back(i);
		}
	}

	for (i = 1; i <= n; i++)
		if ((deg[i] % 2) != 0) return 0;

	for (k = 1; k <= n; k++)
        	for (war[k][k]=1, i = 1; i <= n; i++)
			if (war[i][k])
				for (j = 1; j <= n; j++)
					war[i][j] |= war[k][j];

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			if (war[i][j] == 0) return 0;

	for (i = 1; i <= n; i++)
		need[i] = deg[i] / 2;

	for (i = 0; i < m; i++)
		if (ed[i]) {
			em[i]=ey[i];
			if (--need[ey[i]] < 0) return 0;
		}

	for (i = 1; i <= n; i++)
		for (; need[i] > 0; need[i]--) {
			memset(seen, 0, sizeof(seen));
			if (!aug(i)) return 0;
		}

	for (i = 1; i <= n; i++)
		adj[i].clear();

	/* create fully directed graph from matching with _reversed_ edges */
	for (i = 0; i < m; i++)
		if (ed[i] || ey[i]==em[i])
			adj[ey[i]].push_back(ex[i]);
		else
			adj[ex[i]].push_back(ey[i]);

	m = 0;
	tour(1);
	printf("\n");

	return 1;
}

int main()
{
	int i, t;
	char d;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 0; i < m; i++) {
			scanf("%d %d %c", &ex[i], &ey[i], &d);
			ed[i] = (d == 'D' || d == 'd');
		}

		if (!solve()) printf("No euler circuit exist\n");
		if (t) printf("\n");
	}

	return 0;
}
