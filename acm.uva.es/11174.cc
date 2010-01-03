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

/* Finds g = gcd(a,b) and x,y such that ax + by = g (mod m). */
template<typename T> void gcdextm(T &g, T &x, T &y, T a, T b, T m) {
	if (b == 0) {
		g = a; x = 1; y = 0;
	} else {
		gcdextm(g, y, x, b, a % b, m);
		y -= ((a / b) * x) % m;
		while (y < 0) y += m;
	}
}

/* Modular inverse.
   Returns x such that ax = 1 (mod m), or -1 if no such x exists. */
template<typename T> T modinv(T a, T m) {
	T g, x, y;
	gcdextm(g, x, y, a, m, m);
	if (g < 0) g = -g;
	assert(g == 1);
	return (g == 1) ? (x % m) : -1;
}


int N;
long long fact[50000], factInv[50000], ways[50000], MOD=1000000007;
vector<int> kids[50000];
int size[50000], parent[50000];

long long mul(long long x, long long y) { return (x * y) % MOD; }

long long merge(int a, int b) {
	return mul(mul(fact[a+b], factInv[a]), factInv[b]);
}

void rec(int x) {
	ways[x] = 1;
	size[x] = 1;
	for (int i = 0; i < (int)kids[x].size(); i++) {
		int y = kids[x][i];
		rec(y);
		ways[x] = mul(mul(ways[x], ways[y]), merge(size[x]-1, size[y]));
		size[x] += size[y];
	}
}

int main() {
	fact[0] = 1;
	for (int i = 1; i < 50000; i++)
		fact[i] = (fact[i-1] * i) % MOD;

	for (int i = 0; i < 50000; i++)
		factInv[i] = modinv<long long>(fact[i], MOD);

	int M, T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i <= N; i++) { kids[i].clear(); parent[i] = -1; }
		for (int i = 0; i < M; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			kids[b].push_back(a);
			parent[a] = b;
		}

		for (int x = 1; x <= N; x++)
			if (parent[x] < 0) kids[0].push_back(x);

		rec(0);
		printf("%lld\n", ways[0]);
	}
}
