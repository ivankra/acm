#include <stdio.h>
#include <string.h>

int a[32][32], n;

void erase(int y, int x)
{
	static int s[4096], t;
	int dx, dy;

	t = 0;
	s[t++] = y;
	s[t++] = x;
	a[y][x] = 0;

	while (t > 0) {
		x = s[--t];
		y = s[--t];

		for (dy = -1; dy <= 1; dy++)
			for (dx = -1; dx <= 1; dx++)
				if (a[y + dy][x + dx]) {
					s[t++] = y + dy;
					s[t++] = x + dx;
					a[y + dy][x + dx] = 0;
				}
	}
}

int main()
{
	int i, j, k, t;

	for (t = 1; scanf("%d", &n) == 1; t++) {
		memset(a, 0, sizeof(a));

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n && (k = getchar()) != EOF;)
				if (k == '0' || k == '1') a[i][j++] = k - '0';

		for (k = 0, i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (a[i][j]) k++, erase(i, j);

		printf("Image number %d contains %d war eagles.\n", t, k);
	}

	return 0;
}
