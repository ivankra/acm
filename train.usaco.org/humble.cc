/*
ID: infnty1
PROB: humble
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }

int a[128], p[128], h[131072], n, k;

int main()
{
	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);

	scanf("%d %d", &k, &n);
	for (int i = 0; i < k; i++) scanf("%d", &p[i]);

	qsort(p, k, sizeof(p[0]), &cmp);

	memset(a, 0, sizeof(a));
	h[0] = 1;

	for (int i = 1; i <= n; i++) {
		h[i] = 0x7FFFFFFF;
		for (int j = 0; j < k; j++) {
			while (h[a[j]]*p[j] <= h[i-1]) a[j]++;
			h[i] <?= h[a[j]]*p[j];
		}
	}

	printf("%d\n", h[n]);

	return 0;
}
