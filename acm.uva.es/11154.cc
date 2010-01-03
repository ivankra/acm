#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Road {
	int a, b;
};

Road R[64];
int N, adj[64][64], deg[64], order[64];
int color[64], K;

bool rec(int i = 0, int mx = 0) {
	if (i == N) return true;

	int x = order[i];

	for (int j = i; j < N; j++) {
		long long t = ((1<<K)-1) << 1;
		for (int y = 0; y < N; y++)
			t &= ~(((long long)adj[order[j]][y]) << color[y]);
		if (t == 0) return false;
	}

	long long occ = 0;
	for (int y = 0; y < N; y++)
		occ |= ((long long)adj[x][y]) << color[y];

	for (color[x] = 1; color[x] <= K && color[x] <= mx+1; color[x]++) {
		if (((occ >> color[x]) & 1) != 0) continue;
		if (rec(i+1, max(mx, color[x]))) return true;
	}
	color[x] = 0;

	return false;
}

bool cmp(int i, int j) { return deg[i] > deg[j]; }

int solve(int levels) {
	for (int i = 0; i < N; i++) {
		deg[i] = 0;
		for (int j = 0; j < N; j++)
			deg[i] += adj[i][j];
	}

	for (int i = 0; i < N; i++) order[i] = i;
	sort(order, order+N, cmp);

	int left = 3 + min(2, levels-1);
	int right = N;
	while (left < right) {
		K = (left + right) / 2;
		memset(color, 0, sizeof(color));
		if (rec())
			right = K;
		else
			left = K + 1;
	}
	return left;
}

void addRoad(int a, int b) {
	if (a > b) swap(a, b);
	for (int i = 0; i < N; i++)
		if (R[i].a == a && R[i].b == b) return;
	assert(N+1 <= 64);
	R[N].a = a;
	R[N].b = b;
	N++;
}

int getRoad(int a, int b) {
	if (a > b) swap(a, b);
	for (int i = 0; i < N; i++)
		if (R[i].a == a && R[i].b == b) return i;
	return -1;
}

int main()
{
	int L1, L2, M;
	while (scanf(" %o %o %o", &L1, &L2, &M) == 3 && L1 <= L2) {
		assert(0 <= L1 && L2-L1 <= 2);

		N = 0;
		for (int lev = L1; lev <= L2; lev++) {
			for (int i = 0; i < 8; i++) {
				addRoad(lev*8+i, lev*8+(i+1)%8);
				if (lev+1 <= L2)
					addRoad((lev+1)*8+i, lev*8+i);
			}
			addRoad(lev*8, lev*8+4);
		}

		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) continue;

				if (R[i].a == R[j].a || R[i].a == R[j].b ||
				    R[i].b == R[j].a || R[i].b == R[j].b)
					adj[i][j] = adj[j][i] = 1;
			}
		}

		for (int i = 0; i < M; i++) {
			int a, b, c, d;
			assert(scanf(" %o %o %o %o", &a, &b, &c, &d) == 4);

			int r1 = getRoad(a, b);
			int r2 = getRoad(c, d);
			if (r1 == r2 || r1 < 0 || r2 < 0) continue;
			adj[r1][r2] = adj[r2][r1] = 1;
		}

		printf("%o\n", solve(L2-L1+1));
	}
}
