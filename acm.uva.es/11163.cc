#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

int N, lim, next;
int a[64], adj[64][8], f[64][64], dist, estim;

bool dfs(int p, int prev) {
	if (estim == 0) return true;

	if (dist + estim > lim) {
		next <?= dist + estim;
		return false;
	}

	for (int i = 0; adj[p][i] >= 0; i++) {
		int q = adj[p][i];
		if (q == prev) continue;

		estim -= f[q][a[q]];
		swap(a[p], a[q]);
		estim += f[p][a[p]];
		dist++;

		if (dfs(q, p))
			return true;

		dist--;
		estim -= f[p][a[p]];
		swap(a[p], a[q]);
		estim += f[q][a[q]];
	}

	return false;
}

int main()
{
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
			f[i][j] = abs(i/4 - j/4) + min(abs(i%4 - j%4), 4 - abs(i%4 - j%4));

	for (int cs = 1; scanf(" %d", &N) == 1 && N > 0; cs++) {
		int pos;
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);
			a[i]--;
			if (a[i] == 0) pos = i;
		}

		for (int i = 0; i < N; i++) {
			int k = 0;
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx == 0 && dy == 0) continue;
					if (dx != 0 && dy != 0) continue;
					int y = i / 4 + dy;
					int x = ((i % 4) + dx + 4) % 4;
					if (y < 0 || y >= N/4) continue;
					adj[i][k++] = y*4 + x;
				}
			}
			adj[i][k] = -1;
		}

		for (lim = 0;;) {
			next = 1<<30;
			dist = 0;

			estim = 0;
			for (int i = 0; i < N; i++)
				if (a[i] != 0) estim += f[i][a[i]];

			if (dfs(pos, -1)) break;
			lim = next;
		}

		printf("Set %d:\n%d\n", cs, lim);
	}
}
