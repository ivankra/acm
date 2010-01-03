#include <stdio.h>

void solve()
{
	static int tc[2048], tr[2048], n, m, t, a;
	int i, j, k;

	scanf("%d %d %d", &n, &t, &m);

	for (tc[0] = tr[0] = 0, i = 1; i <= m && scanf("%d", &a) == 1; i++) {
		tc[i] = tr[i] = 0x7FFFFFFF;
		for (k = 1; k <= n && k <= i; k++) {
			j = 2 * t + ((tc[i - k] > a) ? tc[i - k] : a);
			if (j < tc[i] || (j == tc[i] && tr[i - k] < tr[i])) {
				tc[i] = j;
				tr[i] = tr[i - k] + 1;
			}
		}
	}

	printf("%d %d\n", tc[m] - t, tr[m]);
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;)
		solve();

	return 0;
}
