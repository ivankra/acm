#include <stdio.h>
#include <string.h>

int d[32][32], r[32], u[32], c, z;

void find(int k)
{
	static int s[32], v[32], t;
	int x, y;

	x = r[k - 1];

	if (x == z) {
		for (c++, printf("1"), x = 1; x < k; x++)
			printf(" %d", r[x]);
		printf("\n");
		return;
	}

	memset(v, 0, sizeof(v));
	for (s[0] = x, t = 1; t > 0 && v[z] == 0;)
		for (x = s[--t], y = 1; y <= 20; y++)
			if (d[x][y] && v[y] == 0) v[s[t++] = y] = 1;

	if (v[z] == 0)
		return;

	for (x = r[k - 1], y = 1; y <= 20; y++) {
		if (u[y] == 0 && d[x][y]) {
			u[y] = 1;
			r[k] = y;
			d[x][y] = d[y][x] = 0;
			find(k + 1);
			d[x][y] = d[y][x] = 1;
			u[y] = 0;
		}
	}		
}

int main()
{
	int t, x, y;

	for (t = 1; scanf("%d", &z) == 1 && z > 0; t++) {
		printf("CASE %d:\n", t);

		memset(d, 0, sizeof(d));
		memset(u, 0, sizeof(u));
		while (scanf("%d %d", &x, &y) == 2 && x > 0)
			d[x][y] = d[y][x] = 1;

		c = 0;
		u[1] = 1;
		r[0] = 1;
		find(1);

		printf("There are %d routes from the firestation to streetcorner %d.\n",
			c, z);
	}

	return 0;
}
