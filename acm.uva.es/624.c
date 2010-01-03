#include <stdio.h>
#include <string.h>
#include <ctype.h>

int a[32], r[32], c[32], n, k, s;

void solve(int p, int u)
{
	if (u > n)
		return;

	if (u > s) {
		s = u;
		memcpy(r, c, sizeof(c));
	}

	for (; p < k; p++) {
		c[p] = 1;
		solve(p + 1, u + a[p]);
		c[p] = 0;
	}
}

int main()
{
	int i;

	while (scanf("%d %d", &n, &k) == 2) {
		for (i = 0; i < k; i++)
			scanf("%d", &a[i]);

		s = 0;
		memset(r, 0, sizeof(r));
		memset(c, 0, sizeof(c));

		solve(0, 0);

		for (i = 0; i < k; i++)
			if (r[i]) printf("%d ", a[i]);
		printf("sum:%d\n", s);
	}

	return 0;
}
