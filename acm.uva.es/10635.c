#include <stdio.h>
#include <string.h>

int a[65536], b[65536];

int solve()
{
	int i, j, c, t, k, p;

	if (a[0] < 0) return 0;
	b[k = 1] = a[0];

	for (p = 1; a[p] >= 0; p++) {
		t = a[p];
		if (t > b[k]) {
			b[++k] = t;
			continue;
		}

		for (i = 1, j = k; i < j;) {
			if (b[c = (i + j) >> 1] <= t)
				i = c + 1;
			else
				j = c;
		}
		b[i] = t;
	}

	return k;
}

int main()
{
	static int map1[65536], map2[65536];
	int i, c, t, p, q, x;

	memset(map1, 0, sizeof(map1));

	for (scanf("%d", &t), c = 1; c <= t; c++) {
		scanf("%*d %d %d", &p, &q);
		for (i = 0; i <= p && scanf("%d", &x) == 1; i++)
			map1[x] = c, map2[x] = i;

		for (i = 0; q-- >= 0 && scanf("%d", &x) == 1;)
			if (map1[x] == c) a[i++] = map2[x];
		a[i] = -1;

		printf("Case %d: %d\n", c, solve());
	}

	return 0;
}
