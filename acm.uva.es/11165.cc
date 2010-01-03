#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

// 1: not seen
// 2: reachable at current distance
// 4: reachable at (current distance)+1

int N, Nreal, src, dst;
char tree[263000];

struct Forbidden {
	int u, a, b;
	bool operator <(const Forbidden &f) const {
		if (u != f.u) return u < f.u;
		if (a != f.a) return a < f.a;
		return b < f.b;
	}
} forb[42000];

int forbPos[101000];

void update(int i, int val) {
	i += N;
	tree[i] = val;
	while (i > 1) { i >>= 1; tree[i] = tree[i+i] | tree[i+i+1]; }
}

int next(int i, int mask) {
	i += N;
	if (tree[i] & mask) return i-N;

	int k = 0;
	for (;;) {
		if ((i & 1) == 0 && (tree[i+1] & mask) == mask) { i++; break; }
		if (i == 1) return 1<<30;
		i >>= 1;
		k++;
	}

	for (; k > 0; k--)
		i = ((tree[i+i] & mask) == mask) ? (i+i) : (i+i+1);
	return i-N;
}

void expand(int a, int b) {
//printf("    expand %d..%d\n", a, b);
	for (;;) {
		a = next(a, 1);
		if (a > b) return;
		update(a, 4);
		a++;
	}
}

void expandNode(int x) {
	int y = 0;
	for (int i = forbPos[x]; forb[i].u == x; i++) {
//printf("    forbidden %d..%d\n", forb[i].a, forb[i].b);
		if (y < forb[i].a)
			expand(y, forb[i].a-1);
		y >?= forb[i].b + 1;
	}
	if (y < Nreal)
		expand(y, Nreal-1);
}

int solve() {
	memset(tree, 1, N+N);
	update(src, 2);

	int dist = 0;
	for (;;) {
		if ((tree[N+dst] & 2) == 2) return dist;
//printf("distance=%d\n", dist);
		int x = next(0, 2);
		if (x >= Nreal) break;

		while (x < Nreal) {
//printf("  x=%d\n", x);
			update(x, 0);
			expandNode(x);
			x = next(x+1, 2);
		}

		x = next(0, 4);
		while (x < Nreal) {
			update(x, 2);
			x = next(x+1, 4);
		}
		dist++;
	}

	return -1;
}

int main() {
	int K, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &Nreal, &K) == 2; cs++) {
		for (N = 4; N < Nreal+10; N *= 2);
		for (int i = 0; i < K; i++)
			scanf("%d %d - %d", &forb[i].u, &forb[i].a, &forb[i].b);
		scanf("%d %d", &src, &dst);

		sort(forb, forb+K);
		for (int i = 0; i < Nreal; i++) forbPos[i] = 0;
		for (int i = K-1; i >= 0; i--) forbPos[forb[i].u] = i;
		forb[K].u = -1;

		int res = solve();
		printf("Case #%d: ", cs);
		if (res < 0)
			printf("Impossible\n");
		else
			printf("%d\n", res);
	}
}
