#include <cstdio>
#include <cstring>

char a[64][64], b[64][64];
int N, M, n, m, S;

bool check() {
	for (int y = -n-1; y <= N; y++) {
		for (int x = -m-1; x <= M; x++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (b[i][j] != '*') continue;
					if (y+i < 0 || x+j < 0 || y+i >= N || x+j >= M || a[y+i][x+j] == '.')
						goto skip;
				}
			}
			return true;
skip:;
		}
	}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N, &M, &S);
		memset(a, '.', sizeof(a));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				scanf(" %c", &a[i][j]);

		for (int s = 1; s <= S; s++) {
			scanf("%d %d", &n, &m);
			memset(b, '.', sizeof(b));
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					scanf(" %c", &b[i][j]);
			printf(check() ? "Yes\n" : "No\n");
		}

		printf("\n");
	}
}
