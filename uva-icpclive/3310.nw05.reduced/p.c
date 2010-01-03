#include <stdio.h>

int a[1024], n;
int b[1048576], id=42;

int solve()
{
	int i, j, m;

	for (m = n; ; m++) {
		id++;
		for (i = 0; i < n; i++) {
			j = a[i] % m;
			if (b[j] == id) break;
			b[j] = id;
		}
		if (i == n) return m;
	}
}

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++) scanf("%d", &a[i]);
		printf("%d\n", solve());
	}

	return 0;
}
