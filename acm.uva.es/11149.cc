#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int N;

void Mul(int C[64][64], int A[64][64], int B[64][64]) {
	static int t[64][64];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			t[i][j] = 0;
			for (int k = 0; k < N; k++)
				t[i][j] += A[i][k] * B[k][j];
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			C[i][j] = (t[i][j] % 10);
}

void rec(int pwr[64][64], int sum[64][64], int A[64][64], int K) {
	if (K == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				pwr[i][j] = sum[i][j] = 0;
			pwr[i][i] = 1;
		}
		return;
	}

	if ((K % 2) == 0) {
		rec(pwr, sum, A, K/2);

		static int C[64][64];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				C[i][j] = pwr[i][j];
			C[i][i] = (C[i][i] + 1) % 10;
		}
		Mul(sum, sum, C);

		Mul(pwr, pwr, pwr);
	} else {
		rec(pwr, sum, A, K-1);
		Mul(pwr, pwr, A);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sum[i][j] = (sum[i][j] + pwr[i][j]) % 10;
	}
}

int main()
{
	int A[64][64], P[64][64], S[64][64], K;

	while (scanf("%d %d", &N, &K) == 2 && N > 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &A[i][j]);
				A[i][j] %= 10;
			}
		}

		rec(P, S, A, K);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf(j == 0 ? "%d" : " %d", S[i][j]%10);
			printf("\n");
		}
		printf("\n");
	}
}
