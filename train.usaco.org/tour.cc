/*
ID: infnty1
PROB: tour
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int main() {
	int adj[128][128], N, M;
	char s[256], t[256];

	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);

	scanf("%d %d", &N, &M);

	map<string, int> city;
	for (int i = 0; i < N; i++) {
		scanf(" %s", s);
		city[s] = i;
	}

	memset(adj, 0, sizeof(adj));
	while (M-- > 0 && scanf(" %s %s", s, t) == 2)
		adj[city[s]][city[t]] = adj[city[t]][city[s]] = 1;

	int f[128][128];

	for (int x = N-1; x >= 0; x--)
	for (int y = N-1; y >= 0; y--) {
		int &res = f[x][y];
		res = -(1 << 30);

		if (x==N-1 && y==N-1) { res = 0; continue; }

		for (int z = max(x,y)+1; z < N; z++) {
			if (adj[x][z] && z != y) res >?= f[z][y] + 1;
			if (adj[y][z] && z != x) res >?= f[x][z] + 1;
		}
		if (adj[x][N-1] && adj[y][N-1]) res >?= 1;
	}

	printf("%d\n", max(f[0][0], 0)+1);
}
