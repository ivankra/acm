#include <stdio.h>
#include <string.h>

int x[1024], y[1024], v[1024], n;

int dfs(int a)
{
	int i, k, r, b, c;

	if (a < 0 || v[a]++)
		return 0;

	for (b = -1, r = 0, i = 0; i < n; i++) {
		if (i == a) continue;

		k = (x[i] - x[a]) * (x[i] - x[a]) + (y[i] - y[a]) * (y[i] - y[a]);

		if (b < 0 || k < r ||
		   (k == r && ((x[i] < x[b]) || (x[i] == x[b] && y[i] < y[b]))))
			b = i, r = k;
	}

	for (c = -1, r = 0, i = 0; i < n; i++) {
		if (i == a || i == b) continue;

		k = (x[i] - x[a]) * (x[i] - x[a]) + (y[i] - y[a]) * (y[i] - y[a]);

		if (c < 0 || k < r ||
		   (k == r && ((x[i] < x[c]) || (x[i] == x[c] && y[i] < y[c]))))
			c = i, r = k;
	}

	return (dfs(b) + dfs(c) + 1);
}

int main()
{
	int i;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);

		memset(v, 0, sizeof(v));

		if (dfs(0) == n)
			printf("All stations are reachable.\n");
		else
			printf("There are stations that are unreachable.\n");
	}

	return 0;
}
