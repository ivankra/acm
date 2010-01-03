/*
ID: mjf28791
PROG: lamps
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int on[1024], off[1024], n, c;

int possible(int s)
{
	int n;

	for (n = 0; s > 0; s >>= 1)
		n += s & 1;

	return (n <= c) && ((n & 1) == (c & 1));
}

int lamp(int s, int k)
{
	int r = 1;

	if (s & 1) r ^= 1;
	if ((s & 2) != 0 && (k & 1) == 1) r ^= 1;
	if ((s & 4) != 0 && (k & 1) == 0) r ^= 1;
	if ((s & 8) != 0 && ((k - 1) % 3) == 0) r ^= 1;

	return r;
}

int main()
{
	static char a[16][128];
	int i, s, m;

	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);

	scanf("%d %d", &n, &c);
	for (i = 0; scanf("%d", &on[i]) == 1 && on[i] > 0; i++);
	for (i = 0; scanf("%d", &off[i]) == 1 && off[i] > 0; i++);

	for (s = 0, m = 0; s < 16; s++) {
		if (!possible(s)) continue;

		for (i = 0; on[i] > 0 && lamp(s, on[i]) == 1; i++);
		if (on[i] > 0) continue;

		for (i = 0; off[i] > 0 && lamp(s, off[i]) == 0; i++);
		if (off[i] > 0) continue;

		for (i = 1; i <= n; i++)
			a[m][i - 1] = lamp(s, i) + '0';
		a[m++][n] = '\0';
	}

	qsort(a, m, sizeof(a[0]), &strcmp);

	for (i = 0; i < m; i++)
		printf("%s\n", a[i]);

	if (m == 0)
		printf("IMPOSSIBLE\n");

	return 0;
}
