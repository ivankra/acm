// Matrix operations with numbers modulo a given number.
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long i64;

i64 g_mod=0;
typedef vector<i64> VL;
typedef vector<VL> Matrix;

Matrix matrix(int n, i64 d = 1) {
	Matrix A(n, VL(n, 0));
	for (int i = 0; i < n; i++)
		A[i][i] = d;
	return A;
}

Matrix operator +(const Matrix &A, const Matrix &B) {
	int n = A.size(), m = A[0].size();
	Matrix C(n, VL(m, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			C[i][j] = (A[i][j] + B[i][j]) % g_mod;
	return C;
}

Matrix operator *(const Matrix &A, const Matrix &B) {
	int p=A.size(), q=B.size(), r=B[0].size();
	Matrix C(p, VL(r, 0));
	for (int i = 0; i < p; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < q; k++)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % g_mod;
	return C;
}

Matrix operator ^(Matrix A, i64 b) {
	Matrix R = matrix(A.size(), 1);
	for (; b > 0; b >>= 1) {
		if (b & 1) R = R * A;
		A = A * A;
	}
	return R;
}

i64 trace(const Matrix &A) {
	i64 res = 0;
	for (int i = 0; i < (int)A.size(); i++)
		res = (res + A[i][i]) % g_mod;
	return res;
}

// BEGIN CUT HERE
ostream &operator <<(ostream &o, const Matrix &A) {
	for (int i = 0; i < (int)A.size(); i++) {
		for (int j = 0; j < (int)A[i].size(); j++)
			o << (j ? " " : "") << A[i][j];
		o << endl;
	}
	return o << endl;
}
// ENC CUT HERE
