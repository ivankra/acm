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

enum { MAXN = 10000 };
int a[MAXN], N;

void mul(int k) {
	int carry = 0;
	for (int i = 0; i < N; i++) {
		carry += a[i] * k;
		a[i] = carry % 10;
		carry /= 10;
	}

	while (carry > 0) {
		assert(N+2 < MAXN);
		a[N++] = carry % 10;
		carry /= 10;
	}
}

bool isprime(int n) {
	for (int p = 2; p*p <= n; p++)
		if (n % p == 0) return false;
	return true;
}

int main() {
	int K;
	cin >> K;

	memset(a, 0, sizeof(a));
	a[0] = 1;
	N = 1;

	for (int p = 2; K > 0; p++) {
		if (isprime(p)) { mul(p); K--; }
	}

	for (int i = N-1; i >= 0; i--) putchar('0'+a[i]);
	printf("\n");
}
