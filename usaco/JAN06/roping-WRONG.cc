/*
ID: infnty1
TASK: roping
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct { int x, y; } V[256], C[256];
int memo[256][256][2], diag[256][256], N, G, R;

int getdiag(int i, int j)
{
	int k;

	i %= N;
	j %= N;
	if (i > j) swap(i, j);

	if (i == j || (i+1)%N == j || (j+1)%N == i)
		return 0;

	long double a = V[j].y - V[i].y, b = V[i].x - V[j].x;
	long double c = a * V[i].x + b * V[i].y;
	long double s = sqrt(a * a + b * b);

	for (k = 0; k < G; k++) {
		long double d = (a * C[k].x + b * C[k].y - c) / s;
		if (d < 0) d = -d;

		if (d <= R + 1e-9) return 0;
	}

	return 1;
}

int f(int a, int n, int z)
{
	if (memo[a][n][z] >= 0) return memo[a][n][z];

	if (z == 0) {
		if (n <= 2) return memo[a][n][z] = 0;
	} else {
		if (n <= 1) return memo[a][n][z] = 0;
	}

	memo[a][n][z] = f(a+1, n-1, 1) >? f(a, n-1, 1);
	if (z) memo[a][n][z] >?= diag[a][a+n] + f(a, n, 0);

	for (int c = a+2; c <= a+n-1; c++)
		if (diag[a][c])
			memo[a][n][z] >?= 1 + f(a, c-a, 0) + f(c, a+n-c, 0);

printf("f(%d,%d,%d) = %d\n",a+1,a+1+n,z,memo[a][n][z]);

	return memo[a][n][z];
}

int main()
{
	freopen("roping.in", "r", stdin);
	//freopen("roping.out", "w", stdout);

	scanf("%d %d %d", &N, &G, &R);

	for (int i = 0; i < N; i++)
		scanf("%d %d", &V[i].x, &V[i].y);

	for (int i = 0; i < N; i++)
		scanf("%d %d", &C[i].x, &C[i].y);

	memset(diag, 0, sizeof(diag));
	for (int i = 0; i < N; i++)
		for (int j = i+1; j < N; j++)
			diag[i][j] = diag[j][i] = getdiag(i, j);

#if 1
	printf("Possible diagonals:\n");
	for (int i = 0; i <= N; i++)
		for (int j = i+1; j <= N; j++)
			diag[i][j] && printf("%d - %d\n", i+1, j+1);
#endif

	memset(memo, 0xff, sizeof(memo));

	printf("%d\n", f(0, N, 0));

	return 0;
}
