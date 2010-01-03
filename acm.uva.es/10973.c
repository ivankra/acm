#include <stdio.h>
#include <stdlib.h>

int adj[4096], *next, *ref, n;

int solve()
{
	static int w[4096];
	int a, b, x, r;

	for (x = 1; x <= n; x++) w[x] = 0;

	for (r = 0, x = 1; x <= n; x++) {
		for (a = adj[x]; a != 0; a = next[a])
			w[ref[a]] = 1;

		for (a = adj[x]; a != 0; a = next[a])
			for (b = adj[ref[a]]; b != 0; b = next[b])
				r += w[ref[b]];

		for (a = adj[x]; a != 0; a = next[a])
			w[ref[a]] = 0;
	}

	return r;
}

int main()
{
	int i, t, m, x, y, z;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		next = (int *)malloc((m+10) * sizeof(int));
		ref = (int *)malloc((m+10) * sizeof(int));

		for (i = 1; i <= n; i++)
			adj[i] = 0;

		for (i = 1; m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			if (x > y) { z = x; x = y; y = z; }
			ref[i] = y; next[i] = adj[x]; adj[x] = i++;
		}

		printf("%d\n", solve());

		free(ref);
		free(next);
	}

	return 0;
}
