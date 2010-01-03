#include <cstdio>

int main()
{
	int a[64][64], n, m=0, y, x;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	for (int i = 0; i < 2*n-1; i++)
	for (int j = 0; j < 2*n-1; j++) {
		if ((i & 1) == 0)
			y = i - j, x = j;
		else
			y = j, x = i - j;
		if (x < 0 || y < 0 || x >= n || y >= n) continue;
		printf(m++ ? " %d" : "%d", a[y][x]);
	}
	printf("\n");
}
