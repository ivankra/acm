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
using namespace std;

int M, P, inv[128];
int mat[128][128], var[128], seq[128], C[128][128];

bool rowreduce()
{
	int row = 0, col = 0;
	int i, j, k;

	while (row < M && col < P) {
		for (i = row; i < M; i++)
			if (mat[i][col] != 0) break;

		if (i == M) {
			col++;
			continue;
		}

		if (i != row) {
			for (j = 0; j <= P; j++)
				swap(mat[i][j], mat[row][j]);
		}

		k = inv[mat[row][col]];
		for (j = 0; j <= P; j++)
			mat[row][j] = (mat[row][j] * k) % P;

		for (i = 0; i < M; i++) {
			if (i == row) continue;
			k = (P - mat[i][col]) % P;
			if (k == 0) continue;
			for (j = 0; j <= P; j++)
				mat[i][j] = (mat[i][j] + k * mat[row][j]) % P;
		}

		row++;
		col++;
	}

	int m_new = row;

	for (; row < M; row++) {
		if (mat[row][P] != 0) return false;
	}

	M = m_new;
	return true;
}

bool gauss()
{
#if 0
	printf("Matrix:\n");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < P; j++) printf("%d ", mat[i][j]);
		printf("| %d\n", mat[i][P]);
	}
	printf(".\n");
#endif

	if (!rowreduce()) return false;

	vector<bool> freeVar(P, true);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < P; j++) {
			if (mat[i][j] != 0) {
				freeVar[j] = false;
				break;
			}
		}
	}

	// assign zeros to free variables
	for (int i = 0; i < P; i++) {
		if (freeVar[i]) {
			mat[M][i] = 1;
			mat[M][P] = 0;
			M++;
		}
	}
	assert(M == P);

	assert(rowreduce());
	for (int i = 0; i < P; i++) var[i] = mat[i][P];
	return true;
}

bool solve(int N)
{
	if (N >= P) {
		for (int i = 0; i < P; i++) {
			if (seq[i] != -1 && seq[i] != 0) return false;
			seq[i] = 0;
		}
		return true;
	}

	assert(1 <= N && N <= P-1);

	int missing = 0;
	for (int i = 0; i < P; i++)
		if (seq[i] == -1) missing++;
	assert(missing <= N);

	memset(C, 0, sizeof(C));
	for (int i = 0; i <= P; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % P;
		}
	}

	memset(inv, 0, sizeof(inv));
	for (int i = 1; i < P; i++) {
		for (int j = 1; j < P; j++) {
			if ((i * j) % P == 1) inv[i] = j;
		}
		assert(inv[i] != 0);
	}

	memset(mat, 0, sizeof(mat));
	memset(var, 0, sizeof(var));
	M = 0;
	for (int i = 0; i < P; i++) {
		if (seq[i] == -1) continue;
		for (int j = 0; j <= N; j++) {
			mat[M][(i+N-j)%P] = (j%2==0 ? C[N][j] : (P-C[N][j])) % P;
		}
		mat[M][P] = seq[i] % P;
		M++;
	}

	if (!gauss()) return false;

	for (int i = 0; i < P; i++) {
		int z = 0;
		for (int j = 0; j <= N; j++) {
			int coef = (j % 2 == 0 ? C[N][j] : (P-C[N][j])) % P;
			z = ((z + coef * var[(i+N-j)%P]) % P + P) % P;
		}
		if (seq[i] != -1 && z != seq[i]) return false;
		seq[i] = z;
	}

	return true;
}

int main()
{
	int N;
	char s[50];

	while (scanf("%d %d", &P, &N) == 2 && P != 0) {
		assert(2 <= P && P <= 100);

		for (int i = 0; i < P; i++) {
			scanf(" %s", s);
			if (!isdigit(s[0]))
				seq[i] = -1;
			else
				seq[i] = (atoi(s) % P + P) % P;
		}

		if (!solve(N)) {
			printf("Invalid message!\n");
		} else {
			for (int i = 0; i < P; i++)
				printf(i==0 ? "%d" : " %d", seq[i]);
			printf("\n");
		}
	}
}
