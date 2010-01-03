#include <stdio.h>
#include <string.h>

int one[65536], adj[16], n;

int cnt(int a)
{
	int r;
	for (r = 0; a > 0; a >>= 1) r += (a & 1);
	return r;
}

int check(int z)
{
	int i, m = 0, u = ((1 << n) - 1) ^ z;

	for (i = 0; i < n; i++) {
		if (((u >> i) & 1) && (adj[i] & u) == 0) {
			u &= ~(1 << i);
			m++;
		}
	}

	while (u != 0) {
		for (i = 0; i < n; i++)
			if (((u >> i) & 1) && one[adj[i] & u] >= 0) break;
		if (i >= n) return 0;

		for (m++;;) {
			u &= ~(1 << i);
			if ((adj[i] & u) == 0) break;
			i = one[adj[i] & u];
			if (i < 0) return 0;
		}
	}

	return (cnt(z) >= (m - 1));
}

int main()
{
	int i, t, x, y;

	for (i = 0; i < 65536; i++)
		one[i] = -1;

	for (i = 0; i < 16; i++)
		one[1 << i] = i;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		memset(adj, 0, sizeof(adj));
		while (scanf("%d %d", &x, &y) == 2 && x > 0 && y > 0) {
			if (x == y || x > n || y > n) continue;
			adj[x - 1] |= 1 << (y - 1);
			adj[y - 1] |= 1 << (x - 1);
		}

		for (x = 0, y = n; (x >> n) == 0; x++)
			if (cnt(x) < y && check(x)) y = cnt(x);

		printf("Set %d: Minimum links to open is %d\n", t, y);
	}

	return 0;
}
