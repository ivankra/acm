/*
ID: infnty1
PROB: shuttle
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

int Abuf[1000], *A = &Abuf[500], N, M=0;

void move(int x, int y) {
	assert(A[x] != 0); assert(A[y] == 0);
	if (M == 20) { printf("\n"); M=0; }
	printf(M++ ? " %d" : "%d", x+N+1);
	swap(A[x], A[y]);
}

void f(int n) {
	if (n == 1) {
		move(-1, 0);
	} else {
		f(n-1);
		if (n%2 == 0) move(n, n-1); else move(-n, -(n-1));
	}

	if (n%2 == 0)
		for (int i = n; i > -n; i -= 2) move(i-2, i);
	else
		for (int i = -n; i < n; i += 2) move(i+2, i);
}

void g(int n) {
	if (n%2 == 0) {
		move(-(n-1), -n);
		for (int i = -(n-1); i+2 <= n-1; i += 2) move(i+2, i);
	} else {
		move(n-1, n);
		for (int i = n-1; i-2 >= -(n-1); i -= 2) move(i-2, i);
	}
	if (n>1) g(n-1);
}

int main() {
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);

	scanf("%d", &N);

	memset(Abuf, 0, sizeof(Abuf));
	for (int i = -N, j = 1; i <= N; i++)
		if (i != 0) A[i] = j++;

	f(N);
	g(N);
	printf("\n");
}
