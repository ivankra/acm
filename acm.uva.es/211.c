#include <stdio.h>
#include <string.h>

int map[8][8], a[8][8], b[8][8], u[32], nsol;

void print()
{
	int i, j;

	printf("\n");
	for (i = 0; i < 7; i++) {
		printf(" ");
		for (j = 0; j < 8; j++)
			printf("%4d", b[i][j]);
		printf("\n");
	}

	nsol++;
}

void find(int y, int x)
{
	int t;

	for (;; x++) {
		if (x >= 8)
			y++, x = 0;

		if (y >= 7) {
			print();
			return;
		}

		if (b[y][x] == 0)
			break;
	}

	if (x < 7 && b[y][x + 1] == 0 && u[t = map[a[y][x]][a[y][x + 1]]] == 0) {
		u[t] = 1;
		b[y][x] = b[y][x + 1] = t;
		find(y, x + 2);
		b[y][x] = b[y][x + 1] = 0;
		u[t] = 0;
	}

	if (y < 6 && b[y + 1][x] == 0 && u[t = map[a[y][x]][a[y + 1][x]]] == 0) {
		u[t] = 1;
		b[y][x] = b[y + 1][x] = t;
		find(y, x + 1);
		b[y][x] = b[y + 1][x] = 0;
		u[t] = 0;
	}
}

int main()
{
	int i, j, k, t;

	for (i = 0, k = 1; i <= 6; i++)
		for (j = i; j <= 6; j++, k++)
			map[i][j] = map[j][i] = k;

	for (t = 1;; t++) {
		for (i = 0; i < 7; i++)
			for (j = 0; j < 8; j++)
				if (scanf("%d", &a[i][j]) != 1) return 0;

		printf("%sLayout #%d:\n\n", (t == 1) ? "" : "\n\n\n", t);

		for (i = 0; i < 7; i++) {
			printf(" ");
			for (j = 0; j < 8; j++)
				printf("%4d", a[i][j]);
			printf("\n");
		}

		printf("\nMaps resulting from layout #%d are:\n", t);

		nsol = 0;
		memset(b, 0, sizeof(b));
		memset(u, 0, sizeof(u));

		find(0, 0);

		printf("\nThere are %d solution(s) for layout #%d.\n", nsol, t);
	}

	return 0;
}
