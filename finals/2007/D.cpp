// ACM ICPC World Finals 2007
// Problem D. Jacquard Circuits.
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

struct Point { long long x, y; } P[1024];
int N, M;

long long cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

long long abs64(long long x) {
	return x < 0 ? -x : x;
}

long long solve() {
	for (int i = 0; i < N && N >= 3; i++) {
		while (cross(P[(i-1+N)%N], P[i], P[(i+1)%N]) == 0) {
			for (int j = i+1; j < N; j++)
				P[j-1] = P[j];
			N--;
		}
	}
	if (N <= 2) return 0;

	P[N] = P[0];

	long long G = 0, A = 0, B = 0;
	for (int i = 0; i < N; i++) {
		long long dx = abs64(P[i+1].x - P[i].x);
		long long dy = abs64(P[i+1].y - P[i].y);
		long long t = __gcd(dx, dy);
		G = (G == 0 ? t : __gcd(G, t));
		B += t;
		A += P[i].x * P[i+1].y - P[i+1].x * P[i].y;
	}
	A = abs64(A) / G / G;
	B /= G;

	// 2I = 2A - B + 2

	typedef unsigned long long ui64;
	ui64 res = 0;
	for (int i = 1; i <= M; i++) {
		res += ui64(A)*ui64(i)*ui64(i) - ui64(B)*ui64(i) + 2U;
	}
	return res/2;
}

int main() {
	for (int cs = 1; scanf("%d %d", &N, &M) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%lld %lld", &P[i].x, &P[i].y);
		printf("Case %d: %lld\n", cs, solve());
	}
}
