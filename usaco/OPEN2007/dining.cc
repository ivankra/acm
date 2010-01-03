/*
ID: infnty1
LANG: C++
TASK: dining
*/
/*
Solution:
we model the problem as maximum flow in the following graph:

           s              source
        /  |  \           edges of unit capacity from the source to each Fi
    F1    F2    F3...     food types
       ........           edges Fi-Cj of unit capacity for each pair food-cow in the input
    A1    A2    A3        cows
    |     |     |  ...    edges of unit capacity (to ensure that there's at most one path thru each cow)
    B1    B2    B3
       ........           edges Bi-Dj of unit capacity for each pair cow-drink in the input
    D1    D2    D3...     drinks
      \   |    /          edges of unit capacity from each Di to the sink
          t               sink
*/
#include <cstdio>
#include <cstring>

int adj[512][512], source, sink, N;
int seen[512];

void edge(int u, int v) {
	adj[u][v]++;
}

bool dfs(int x) {
	if (x == sink) return true;
	
	if (seen[x]) return false;
	seen[x] = true;

	for (int y = 0; y < N; y++) {
		if (adj[x][y] > 0 && dfs(y)) {
			adj[x][y]--;
			adj[y][x]++;
			return true;
		}
	}

	return false;
}

int maxflow() {
	int flow = 0;
	for (;;) {
		memset(seen, 0, sizeof(seen));
		if (dfs(source)) flow++; else break;
	}
	return flow;
}

int main()
{
	int nC, nF, nD;
	int A[200], B[200], F[200], D[200];

	freopen("dining.in", "r", stdin);
	freopen("dining.out", "w", stdout);

	scanf("%d %d %d", &nC, &nF, &nD);

	N = 0;
	memset(adj, 0, sizeof(adj));

	source = N++;
	sink = N++;

	for (int i = 1; i <= nC; i++) {
		A[i] = N++;
		B[i] = N++;
		edge(A[i], B[i]);
	}

	for (int i = 1; i <= nF; i++) {
		F[i] = N++;
		edge(source, F[i]);
	}

	for (int i = 1; i <= nD; i++) {
		D[i] = N++;
		edge(D[i], sink);
	}

	for (int i = 1; i <= nC; i++) {
		int f, d, x;
		scanf("%d %d", &f, &d);

		for (int j = 0; j < f; j++) {
			scanf("%d", &x);
			edge(F[x], A[i]);
		}

		for (int j = 0; j < d; j++) {
			scanf("%d", &x);
			edge(B[i], D[x]);
		}
	}

	printf("%d\n", maxflow());

	return 0;
}
