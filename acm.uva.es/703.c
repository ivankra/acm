#include <stdio.h>

static void sort(int a[], int n)
{
	int i, j, p, t;

re:	if (n <= 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (p = a[(n - 1) >> 1], i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

int main()
{
	static int a[128][128], p[128], t[262144], n, m;
	int i, j, k;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				scanf("%d", &a[i][j]);

		for (i = 0; i < n; i++)
			for (p[i] = 0, j = 0; j < n; j++) p[i] += a[i][j];

		for (m = 0, i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
/*				if (p[j] != p[i]) continue;*/
				for (k = j + 1; k < n; k++) {
/*					if (p[k] != p[j]) continue;*/

#define PACK(x,y,z) (((x) << 16) | ((y) << 8) | (z))

					if ((a[i][j] | a[j][i] | a[i][k] | a[k][i] | a[k][j] | a[j][k]) == 0) {
						t[m++] = PACK(i,j,k);
					} else if (a[i][j] && a[j][k] && a[k][i]) {
						t[m++] = PACK(i,j,k);
					} else if (a[k][j] && a[j][i] && a[i][k]) {
						t[m++] = PACK(k,j,i);
					}
				}
			}
		}

		if (m > 1) {
			sort(t, m);

			for (i = 1, j = 1; i < m; i++)
				if (t[i] != t[i - 1]) t[j++] = t[i];
			m = j;
		}

		printf("%d\n", m);

		for (i = 0; i < m; i++) {
			printf("%d %d %d\n",
				(t[i] >> 16) + 1,
				((t[i] >> 8) & 0xFF) + 1,
				(t[i] & 0xFF) + 1
			);
		}
	}

	return 0;
}
