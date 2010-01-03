/*
ID: infnty1
PROB: agrinet
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int a[128][128], d[128], v[128], n, r;

int main()
{
	int i, j;

	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	r = 0;
	memset(v, 0, sizeof(v));

	for (i = 0; i < n; i++) d[i] = 0x3FFFFFFF;
	d[0] = 0;

	for (;;) {
		for (i = 0; i < n && v[i]; i++);
		if (i >= n) break;

		for (j = i+1; j < n; j++) if (!v[j] && d[j]<d[i]) i = j;

		r += d[i];
		v[i] = 1;
		for (j = 0; j < n; j++)
			d[j] <?= a[i][j];
	}

	printf("%d\n", r);

	return 0;
}
