#include <stdio.h>
#include <string.h>

int a[16][16], v[8192], n;

void dec(int k, int x, int y, int s)
{
	if (v[k] >= 0) {
		int i, j;
		for (i = 0; i < s; i++)
			for (j = 0; j < s; j++)
				a[y + i][x + j] = v[k];
		return;
	}

	s >>= 1;
	dec(4 * k + 1, x, y, s);
	dec(4 * k + 2, x + s, y, s);
	dec(4 * k + 3, x, y + s, s);
	dec(4 * k + 4, x + s, y + s, s);
}

void decode()
{
	int m, x, y, i;

	scanf("%d", &m);

	for (i = 0; i < 8192; i++)
		v[i] = -1;

	while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
		v[x] = y;

	memset(a, 0, sizeof(a));

	dec(0, 0, 0, n);
}

int main()
{
	static int lx[256], ly[256], p, t;
	int i, j, k;

	for (scanf("%d", &p), t = 1; t <= p && scanf("%d", &n) == 1; t++) {
		decode();
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				lx[a[i][j]] = i;
				ly[a[i][j]] = j;
			}
		}

		decode();

		printf("%sCase %d\n\n", (t == 1) ? "" : "\n", t);
		for (i = 0, k = 0; i < n; i++) {
			for (j = 0; j < n; j++, k++)
				printf("%4d", a[lx[k]][ly[k]]);
			printf("\n");
		}
	}

	return 0;
}
