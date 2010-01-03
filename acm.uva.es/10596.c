#include <stdio.h>

int p[256], d[256];

int f(int x)
{
	int z;
	for (z = x; p[z] != z; z = p[z]);
	return p[x] = z;
}

int main()
{
	int i, n, m, x, y;

	while (scanf("%d %d", &n, &m) == 2) {
		for (i = 0; i < n; i++)
			p[i] = i, d[i] = 0;

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
			d[x]++, d[y]++, p[f(x)] = p[f(y)];

		for (i = 0, x = f(0); i < n && (d[i] & 1) == 0 && f(i) == x; i++);
		printf((i >= n) ? "Possible\n" : "Not Possible\n");
	}

	return 0;
}
