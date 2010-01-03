#include <stdio.h>

int main()
{
	static int parent[32768], count[32768];
	static int r, t, a, b, n, m;
	register int i;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d%d", &n, &m) == 2) {
		for (i = 1; i <= n; i++)
			parent[i] = i;

		for (i = 1; i <= n; i++)
			count[i] = 1;

		for (r = 1; m-- > 0 && scanf("%d%d", &a, &b) == 2;) {
			if (a == b)
				continue;

			for (i = a; parent[i] != i; i = parent[i]);
			a = (parent[a] = i);

			for (i = b; parent[i] != i; i = parent[i]);
			b = (parent[b] = i);

			if (a == b)
				continue;

			if (count[a] >= count[b]) {
				parent[b] = a;
				if ((count[a] += count[b]) > r)
					r = count[a];
			} else {
				parent[a] = b;
				if ((count[b] += count[a]) > r)
					r = count[b];
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
