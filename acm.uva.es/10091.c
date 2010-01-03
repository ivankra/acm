#include <stdio.h>
#include <string.h>

int adj[32][32], deg[32];

void next(double p[])
{
	double q[32];
	int i, j;

	for (i = 0; i < 26; i++)
		q[i] = 0.;

	for (i = 0; i < 26; i++)
		for (j = 0; j < 26; j++)
			if (adj[i][j]) q[j] += p[i] / (double)deg[i];

	for (i = 0; i < 26; i++)
		p[i] = q[i];
}

int main()
{
	double p[32], q[32], r;
	int i, j, n, y, m, d, t;
	char a, b;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d", &y, &m, &d) == 3;) {
		for (n = 0; y < 470 || m != 2 || d >= 14; n++) {
			if (m == 12) y++;
			m = 1 + m % 12;
			d = 1;
		}

		memset(adj, 0, sizeof(adj));
		for (scanf("%d", &m); m-- > 0 && scanf(" %c %c", &a, &b) == 2;)
			adj[a - 'A'][b - 'A'] = adj[b - 'A'][a - 'A'] = 1;

		for (i = 0; i < 26; i++)
			for (adj[i][i] = 1, deg[i] = 0, j = 0; j < 26; j++)
				deg[i] += adj[i][j];

		for (i = 0; i < 26; i++)
			p[i] = q[i] = 0.;

		scanf(" %c %c", &a, &b);

		for (p[a - 'A'] = q[b - 'A'] = 1.; n-- > 0;)
			next(p), next(q);

		for (r = 0., i = 0; i < 26; i++)
			r += p[i] * q[i];

		printf("%.5f\n", r);
	}

	return 0;
}
