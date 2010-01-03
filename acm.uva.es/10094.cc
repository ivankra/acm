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
#include <set>
#include <queue>
using namespace std;

bool check(int a[], int N) {
	static char b[34096];
	memset(b, 0, sizeof(b));

	for (int i = 0; i < N; i++) {
		if (a[i] < 1 || a[i] > N) return false;

		if (b[a[i]] & 1) return false;
		b[a[i]] |= 1;

		if (b[i + a[i]] & 2) return false;
		b[i + a[i]] |= 2;

		if (b[a[i] - i + N] & 4) return false;
		b[a[i] - i + N] |= 4;
	}

	return true;
}

bool gen(int a[], int N) {
	int m;

	m = 0;
	for (int i = 2; i <= N; i += 2) a[m++] = i;
	for (int i = 1; i <= N; i += 2) a[m++] = i;
	if (m == N && check(a, N)) return true;

	m = 0;
	for (int i = 4; i <= N; i += 2) a[m++] = i;
	if (N >= 2) a[m++] = 2;
	for (int i = 5; i <= N; i += 2) a[m++] = i;
	for (int i = 1; i <= 3 && i <= N; i += 2) a[m++] = i;
	if (m == N && check(a, N)) return true;

	m = 0;
	for (int i = 2; i <= N; i += 2) a[m++] = i;
	for (int i = 3; i >= 1; i -= 2) if (i <= N) a[m++] = i;
	for (int i = 7; i <= N; i += 2) a[m++] = i;
	if (5 <= N) a[m++] = 5;
	if (m == N && check(a, N)) return true;

	return false;
}

int main() {
	int a[2048], N;
	while (scanf("%d", &N) == 1 && N > 0) {
		if (!gen(a, N)) {
			printf("Impossible\n");
		} else {
			for (int i = 0; i < N; i++)
				printf(i == 0 ? "%d" : " %d", a[i]);
			printf("\n");
		}
	}
}
