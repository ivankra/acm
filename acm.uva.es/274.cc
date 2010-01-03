#include <stdio.h>
#include <string.h>

int n;

void closure(int a[128][128])
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			if (a[i][k])
				for (int j = 1; j <= n; j++)
					a[i][j] |= a[k][j];
}

int main()
{
	static int rC, rM, T, C[128][128], M[128][128], R[128][128];
	char buf[256];
	int x, y;

	for (scanf("%d", &T); T-->0 && scanf("%d %d %d", &n, &rC, &rM) == 3;) {
		memset(C, 0, sizeof(C));
		memset(M, 0, sizeof(M));

		while (gets(buf)) {
		       if (sscanf(buf, "%d %d", &x, &y) != 2) continue;
		       if (x < 0 || y < 0) break;
		       C[x][y] = 1;
		}

		while (gets(buf) && sscanf(buf, "%d %d", &x, &y)==2 && x >= 0)
		       M[x][y] = 1;

		for (x = 1; x <= n; x++)
			C[x][x] = M[x][x] = 1;

		memcpy(R, M, sizeof(M));
		closure(C);
		closure(M);

		for (x = 1; x <= n; x++)
			if (C[rC][x] && M[rM][x]) break;
		printf(x <= n ? "Y " : "N ");

		for (x = 1; x <= n; x++) {
			if (C[rC][x])
				for (y = 1; y <= n; y++)
					R[y][x] = 0;
			R[x][x] = 0;
		}

		closure(R);
		printf((!C[rC][rM] && R[rM][rM]) ? "Y\n" : "N\n");
		if (T) printf("\n");
	}

	return 0;
}
