/*
ID: mjf28791
PROG: inflate
LANG: C
*/
#include <stdio.h>
#include <string.h>

int main()
{
	static int a[16384], p, t;
	int i, m, n;

	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);

	memset(a, 0, sizeof(a));

	for (scanf("%d %d", &m, &n); n-- > 0 && scanf("%d %d", &p, &t) == 2;)
		for (i = t; i <= m; i++)
			if ((p + a[i - t]) > a[i]) a[i] = p + a[i - t];

	printf("%d\n", a[m]);
	return 0;
}
