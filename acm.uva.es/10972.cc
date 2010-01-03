#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

VVI G; VI C, d, e, low; int T;

int f(int x) {
	int z;
	for (z = x; C[z] != z; z = C[z]);
	return (C[x] = z);
}

void dfs(int p, int x) {
	d[x] = low[x] = T++;
	for (int i = 0; i < G[x].size(); i++) {
		int y = G[x][i];
		if (y == p) continue;
		if (d[y] > 0) {
			C[f(x)] = f(y);
			low[x] <?= d[y];
		} else {
			dfs(x, y);
			low[x] <?= low[y];
			if (low[y] < d[y]) C[f(x)] = f(y);
		}
	}
}


int main()
{
	int n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2) {
		G.clear(); G.resize(n);
		while (m-- && scanf("%d %d", &x, &y) == 2) {
			x--; y--;
			G[x].push_back(y);
			G[y].push_back(x);
		}

		d = VI(n, 0);
		low = VI(n, 0);
		T = 1;

		C = VI(n);
		for (int i = 0; i < n; i++) C[i] = i;

		int nc = 0;
		for (int i = 0; i < n; i++)
			if (d[i] == 0) nc++, dfs(-1, i);

		for (int i = 0; i < n; i++)
			f(i);

		e = VI(n, 0);
		for (x = 0; x < n; x++) {
			for (int i = 0; i < G[x].size(); i++) {
				int y = G[x][i];
				if (C[x] != C[y] && x < y) {
					e[C[x]]++;
					e[C[y]]++;
				}
			}
		}

		int L = 0;
		for (x = 0; x < n; x++)
			if (C[x] == x) {
				if (e[x] == 1) L++;
				if (e[x] == 0 && nc > 1) L += 2;
			}
		printf("%d\n", (L+1)/2);
	}
	return 0;
}
