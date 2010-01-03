// 2D Fenwick tree.
// tags: fenwick, data structures. 
#include <cstdio>

int tree[1024][1024], mat[1024][1024], N;

void add(int x, int y, int value) {
	for (int i = x; i < N; i |= i + 1)
		for (int j = y; j < N; j |= j + 1)
			tree[i][j] += value;
}

int sum(int x, int y) {
	int res = 0;
	for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
		for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
			res += tree[i][j];
	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tree[i][j] = mat[i][j] = 0;

		char cmd[10];
		while (scanf(" %s", cmd) == 1 && cmd[0] != 'E') {
			if (cmd[1] == 'E') {
				int x, y, num;
				scanf("%d %d %d", &x, &y, &num);
				if (mat[x][y] != num) {
					add(x, y, num-mat[x][y]);
					mat[x][y] = num;
				}
			} else {
				int x1, y1, x2, y2;
				scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

				int res = sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
				printf("%d\n", res);
			}
		}
	}
}
