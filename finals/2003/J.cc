// ICPC Finals 2003 - Problem J - Toll
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int adj[64][64], spoons, src, dst;

int solve()
{
	int INF = 0x3fffffff;
	int need[64];
	for (int i = 0; i < 52; i++)
		need[i] = INF;
	need[dst] = spoons;

	for (bool changed = true; changed;) {
		changed = false;

		for (int y = 0; y < 52; y++) {
			if (need[y] >= INF) continue;
			for (int x = 0; x < 52; x++) {
				if (!adj[y][x]) continue;

				int d;
				if (y < 26) {
					d = need[y] + 1;
				} else {
					d = max(need[y] + 1, need[y] * 20 / 19 - 5);
					while (d - (d + 19) / 20 < need[y]) ++d;
				}

				if (d < need[x]) {
					need[x] = d;
					changed = true;
				}
			}
		}
	}

	return need[src];
}

int readCity() {
	char c;
	scanf(" %c", &c);
	return islower(c) ? (c - 'a') : (c - 'A' + 26);
}

int main()
{
	int M;

	for (int cs = 1; scanf("%d", &M) == 1 && M >= 0; cs++) {
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < M; i++) {
			int x = readCity();
			int y = readCity();
			if (x != y) {
				adj[x][y] = adj[y][x] = 1;
			}
		}

		scanf("%d", &spoons);
		src = readCity();
		dst = readCity();

		printf("Case %d: %d\n", cs, solve());
	}
}
