/*
ID: infnty1
TASK: telecow
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int N, cap[256][256], res[256][256];
vector<int> adj[256];

int vin(int x) { return x*2-1; }
int vout(int x) { return x*2-2; }
int vorig(int y) { return (y+2)/2; }

vector<int> seen;
int aug(int x, int sink) {
	if (x == sink) return 1;
	if (seen[x]++) return 0;

	for (int i = 0; i < adj[x].size(); i++) {
		int y = adj[x][i];
		if (res[x][y] > 0 && aug(y, sink)) {
			res[x][y]--;
			res[y][x]++;
			return 1;
		}
	}

	return 0;
}

int flow(int s, int t) {
	for (int x = 0; x < N; x++) {
		for (int i = 0; i < adj[x].size(); i++) {
			int y = adj[x][i];
			res[x][y] = cap[x][y];
		}
	}

	int f = 0;
	for (;;) {
		seen.assign(N, 0);
		if (aug(s, t)) f++; else break;
	}
	return f;
}

int main()
{
	freopen("telecow.in", "r", stdin);
	freopen("telecow.out", "w", stdout);

	int m, s, t;
	scanf("%d %d %d %d", &N, &m, &s, &t);

	N *= 2;
	s = vout(s);
	t = vin(t);
	memset(cap, 0, sizeof(cap));

	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		cap[vout(x)][vin(y)] = 1<<20;
		cap[vout(y)][vin(x)] = 1<<20;
	}

	for (int x = 1; x <= N/2; x++)
		cap[vin(x)][vout(x)] = 1;

	for (int x = 0; x < N; x++) {
		adj[x].clear();
		for (int y = 0; y < N; y++)
			if (cap[x][y] > 0 || cap[y][x] > 0)
				adj[x].push_back(y);
	}

	int f = flow(s, t);
	printf("%d\n", f);

	for (int x = 1, k = 0; f > 0 && x <= N/2; x++) {
		if (x == vorig(s) || x == vorig(t)) continue;

		cap[vin(x)][vout(x)] = 0;
		if (flow(s, t) == f-1) {
			printf(k++ ? " %d" : "%d", x);
			f--;
		} else {
			cap[vin(x)][vout(x)] = 1;
		}
	}
	printf("\n");
}
