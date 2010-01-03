/*
ID: infnty1
PROB: gift1
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int main()
{
	int a[16], i, j, k, m, n;
	char z[16][16], s[100];

	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);

	memset(a, 0, sizeof(a));

	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf(" %s", z[i]);

	for (j = 0; j < n; j++) {
		scanf(" %s %d %d", s, &m, &k);
		if (k < 1) continue;

		for (i = 0; i < n; i++)
			if (strcmp(s, z[i]) == 0) break;

		a[i] += (m % k) - m;
		for (m /= k; k-- > 0;) {
			scanf(" %s", s);
			for (i = 0; i < n; i++)
				if (strcmp(s, z[i]) == 0) {
					a[i] += m;
					break;
				}
		}
	}

	for (i = 0; i < n; i++)
		printf("%s %d\n", z[i], a[i]);
	return 0;
}
