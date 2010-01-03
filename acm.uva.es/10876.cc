#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int N;
struct { int x, y, r; } C[256];

int uf[256];

int f(int x) {
	int z;
	for (z = x; uf[z] != z; z = uf[z]);
	while (x != z) { int y = uf[x]; uf[x] = z; x = y; }
	return z;
}

void merge(int x, int y) { uf[f(x)] = f(y); }

double sq(double x) { return x * x; }

bool possible(double R) {
	for (int i = 0; i < N+4; i++) uf[i] = i;

	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			double t = sqrt(sq(C[i].x-C[j].x) + sq(C[i].y-C[j].y)) - C[i].r - C[j].r;
			if (t < 2*R)
				merge(f(i), f(j));
		}

		if (C[i].x-C[i].r < 2*R) merge(i, N+0);
		if (1000-C[i].x-C[i].r < 2*R) merge(i, N+1);
		if (C[i].y-C[i].r < 2*R) merge(i, N+2);
		if (1000-C[i].y-C[i].r < 2*R) merge(i, N+3);
	}

	for (int i = 0; i < 4; i++)
		for (int j = i+1; j < 4; j++)
			if (f(N+i) == f(N+j)) return false;
	return true;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &C[i].x, &C[i].y, &C[i].r);

		double left = 0, right = 500;
		while (right - left > 1e-9) {
			double mid = (left + right) / 2;
			if (possible(mid)) left = mid; else right = mid;
		}
		printf("%.3f\n", left);
	}
}
