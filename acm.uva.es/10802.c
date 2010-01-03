#include <stdio.h>
#include <string.h>

int deg[128], adjm[128][128], adjl[128][128], n;

int deadend(int p0, int s0, int g)
{
	static int p[128], s[128], v[128];
	int i, j, t;

	memset(v, 0, sizeof(v));

	p[0] = p0;
	s[0] = s0;
	v[s0] = v[p0] = 1;
	t = 1;

	while (t-- > 0) {
		s0 = s[t];
		p0 = p[t];

		if (s0 == g)
			return 0;

		for (i = 0; i < deg[s0]; i++) {
			j = adjl[s0][i];
			if (j == p0) continue;
			if (v[j]++) return 0;
			s[t] = j;
			p[t] = s0;
			t++;
		}
	}

	return 1;
}

int solve(int s, int t)
{
	static int v[128][128], p[65536];
	int i, j, k, z;

	memset(v, 0, sizeof(v));

	for (k = 0, z = n; s != t;) {
		if (v[z][s]++) return 1;
		p[k++] = s;

		for (i = 0; i < deg[s]; i++) {
			j = adjl[s][i];
			if (j != z && !deadend(s, j, t)) break;
		}

		if (i >= deg[s]) return 1;

		z = s;
		s = j;
	}

	for (i = 0; i < k; i++)
		printf("%d ", p[i]);
	printf("%d\n", t);

	return 0;
}

int main()
{
	int i, j, m, c, s, t, x, y;

	scanf("%d", &t);

	for (c = 1; c <= t && scanf("%d %d %d", &n, &m, &s) == 3; c++) {
		printf("Case #%d:\n", c);

		memset(adjm, 0, sizeof(adjm));
		while (m-- > 0 && scanf("%d %d", &x, &y) == 2)
			if (x != y && adjm[x][y] == 0)
				adjm[x][y] = adjm[y][x] = 1;

		for (i = 0; i < n; i++)
			for (deg[i] = 0, j = 0; j < n; j++)
				if (adjm[i][j]) adjl[i][deg[i]++] = j;

		for (i = 0; i < n; i++)
			if (solve(s, i)) printf("No drive.\n");

		printf("\n");
	}

	return 0;
}
