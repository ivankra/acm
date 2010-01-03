/*
ID: infnty1
LANG: C++
TASK: sumsums
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

long long MOD = 98765431;

struct Matrix {
	long long a[2][2];
	Matrix() { memset(a, 0, sizeof(a)); }
	long long operator()(int i, int j) const { return a[i][j]; }
	long long &operator()(int i, int j) { return a[i][j]; }
};

Matrix mul(Matrix A, Matrix B) {
	Matrix C;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			C(i, j) = 0;
			for (int k = 0; k < 2; k++)
				C(i, j) = (C(i, j) + A(i, k) * B(k, j)) % MOD;
		}
	}
	return C;
}

Matrix pow(Matrix A, int N)
{
	Matrix res;
	res(0, 0) = res(1, 1) = 1;

	while (N != 0) {
		if (N & 1)
			res = mul(res, A);
		A = mul(A, A);
		N >>= 1;
	}

	return res;
}

int main()
{
	freopen("sumsums.in", "r", stdin);
	freopen("sumsums.out", "w", stdout);

	int N, T;
	scanf("%d %d", &N, &T);

	vector<int> C(N);
	long long S = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &C[i]);
		S = (S + C[i]) % MOD;
	}

	Matrix A;
	A(0, 0) = (N - 1) % MOD;   A(0, 1) = 1;
	A(1, 0) = 0;               A(1, 1) = MOD - 1;

	A = pow(A, T);

	for (int i = 0; i < N; i++) {
		long long z = (A(0, 1) * S + A(1, 1) * C[i]) % MOD;
		printf("%lld\n", z);
	}

	return 0;
}
