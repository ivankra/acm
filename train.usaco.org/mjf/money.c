/*
ID: mjf28791
PROG: money
LANG: C
*/
#include <stdio.h>

int main()
{
	static long long w[16384];
	int i, j, n, v, x;

	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);

	scanf("%d %d", &v, &n);

	for (w[0] = 1, i = 1; i <= n; i++)
		w[i] = 0;

	while (v-- > 0 && scanf("%d", &x) == 1)
		for (i = x, j = 0; i <= n;) w[i++] += w[j++];

	printf("%lld\n", w[n]);
	return 0;
}
