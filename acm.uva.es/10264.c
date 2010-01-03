#include <stdio.h>
#include <assert.h>

int main()
{
	static int w[65536], p[65536], n, m, r;
	int i, j;

	while (scanf("%d", &n) == 1) {
		assert(2 <= n && n <= 16);

		m = 1 << n;
		for (i = 0; i < m; i++)
			scanf("%d", &w[i]);

		for (i = 0; i < m; i++)
			for (p[i] = 0, j = 0; j < n; j++)
				p[i] += w[i ^ (1 << j)];

		for (r = i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				if ((p[i] + p[i ^ (1 << j)]) > r)
					r = p[i] + p[i ^ (1 << j)];

		printf("%d\n", r);
	}

	return 0;
}
