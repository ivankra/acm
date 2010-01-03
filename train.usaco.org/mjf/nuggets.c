/*
ID: mjf28791
PROG: nuggets
LANG: C
*/
#include <stdio.h>

#define INF 0x7FFFFFFF

int a[16], b[512], m, n;

void sort()
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

int solve()
{
	int i, j, k, f;

	sort();

	if (a[0] <= 1)
		return 0;

	m = a[0];

	for (i = 0; i < m; i++)
		b[i] = INF;

	for (i = 0; i < n; i++)
		b[a[i] % m] = a[i];

	do {
		for (f = 0, i = 1; i < n; i++)
			for (j = 0; j < m; j++)
				if (b[j] < INF &&
				    b[k = (j + a[i]) % m] > (b[j] + a[i])) {
					b[k] = b[j] + a[i];
					f = 1;
				}
	} while (f);

	for (j = b[0], i = 0; i < m; i++)
		if (b[i] > j) j = b[i];

	return (j == INF) ? 0 : (j - m);
}

int main()
{
	int i;

	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);

	printf("%d\n", solve());
	return 0;
}
