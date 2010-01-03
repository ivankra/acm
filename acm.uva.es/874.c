#include <stdio.h>

#define EMPTY	-1
#define FULL	-2

char map[256][256], flat[65536];
int node[65536][4];

void decode(int n, int x, int y, int s)
{
	int i, j;

	if (s == 1 && n >= 0)
		n = node[n][0];

	if (n == EMPTY) {
		for (i = 0; i < s; i++)
			for (j = 0; j < s; j++) map[y + i][x + j] = 0;
	} else if (n == FULL) {
		for (i = 0; i < s; i++)
			for (j = 0; j < s; j++) map[y + i][x + j] = 1;
	} else {
		i = s >> 1;
		decode(node[n][0], x, y, i);
		decode(node[n][1], x + i, y, i);
		decode(node[n][2], x, y + i, i);
		decode(node[n][3], x + i, y + i, i);
	}
}

int get()
{
	int r, c;

	while ((c = getchar()) != EOF) {
		if (c == 'E') {
			return EMPTY;
		} else if (c == 'F') {
			return FULL;
		} else if ('0' <= c && c <= '9') {
			for (r = 0; '0' <= c && c <= '9'; c = getchar())
				r = r * 10 + c - '0';
			if (c != EOF) ungetc(c, stdin);
			return r;
		}
	}

	return EMPTY;
}

int main()
{
	int i, j, k, n, m, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (i = 1; i <= m; i++) {
			for (j = 0; j < 4; j++)
				node[i][j] = get();
		}

		decode(1, 0, 0, n);

		for (i = 0, k = 0; i < n; i++)
			for (j = 0; j < n; j++)
				flat[k++] = map[i][j];

		for (m = n * n, i = j = 0, k = 1; i < m; i++) {
			if (flat[i] == k) {
				j++;
			} else {
				printf("%d ", j);
				k ^= 1;
				j = 1;
			}
		}
		printf("%d\n", j);

		if (t > 0) printf("\n");
	}

	return 0;
}
