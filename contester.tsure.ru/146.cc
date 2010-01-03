/*
 *  s = number of R-B segments.
 *  x = number of B-B segments.
 *  L = number of R on the border.
 *  Call an arrangement _valid_, if all four corners are colored B.
 *
 *  Proposition.  If two valid arrangements A:(s,x,L) and B:(s',x',L')
 *  contain the same number of R and B points, then there exists
 *  integers a and b such that:
 *     s' = s + 2a + b
 *     x' = x - a
 *     L' = L + b
 */

#include <cstdio>
#include <cstring>

int a[128][128], N, R, B, S1, L1, X, S, L;

int main()
{
	scanf("%d %d %d %d", &N, &S1, &R, &L1);
	B = N*N-R;

	memset(a, 0, sizeof(a));
	a[0][0] = a[0][N-1] = a[N-1][0] = a[N-1][N-1] = 1;
	for (int i = 0, k = 4; i < N && k < B; i++)
		for (int j = 0; j < N && k < B; j++)
			if (a[i][j] == 0) { a[i][j] = 1; k++; }

	L = 0;
	for (int i = 1; i < N-1; i++)
		L += (1-a[i][0])+(1-a[0][i])+(1-a[N-1][i])+(1-a[i][N-1]);

	S = 0;
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++)
			S += (a[i][j]^a[i-1][j])+(a[i][j]^a[i][j-1]);
		S += (a[0][i]^a[0][i-1])+(a[i][0]^a[i-1][0]);
	}

	X = 0;
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++)
			X += (a[i][j]&a[i-1][j])+(a[i][j]&a[i][j-1]);
		X += (a[0][i]&a[0][i-1])+(a[i][0]&a[i-1][0]);
	}

	int a = (S1 - S - L1 + L) / 2;
	printf("%d\n", X-a);
}
