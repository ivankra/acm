#include <stdio.h>
#include <math.h>

typedef struct { int x, y; } pt_t;
double hypot(double, double);

int r[256][256], v;

int maxflow()
{
	static int s[256], p[256];
	int i, j, f, t;

	for (f = 0;; f++) {
		for (i = 1; i <= v; i++)
			p[i] = 0;

		for (s[0] = 1, t = 1; t > 0 && p[2] == 0;) {
			for (i = s[--t], j = 1; j <= v; j++) {
				if (r[i][j] && p[j] == 0) {
					p[j] = i;
					s[t++] = j;
				}
			}
		}

		if (p[2] == 0)
			return f;

		for (i = 2; i != 1; i = p[i]) {
			r[p[i]][i] = 0;
			r[i][p[i]] = 1;
		}
	}
}

int main()
{
	static int l1[256], l2[256], n, m, t;
	static pt_t p[128], q[128];
	int i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		n--;

		for (i = 0; i <= n; i++)
			scanf("%d %d", &p[i].x, &p[i].y);

		for (i = 0; i < m; i++)
			scanf("%d %d", &q[i].x, &q[i].y);

		for (v = 2, i = 0; i < n; i++)
			l1[i] = ++v;

		for (i = 0; i < m; i++)
			l2[i] = ++v;

		for (i = 1; i <= v; i++)
			for (j = 1; j <= v; j++) r[i][j] = 0;

		for (i = 0; i < n; i++) {
			for (r[1][l1[i]] = 1, j = 0; j < m; j++) {
				double d;

				d = hypot(p[i].x - q[j].x, p[i].y - q[j].y) +
				    hypot(q[j].x - p[i+1].x, q[j].y - p[i+1].y)
				    - 2. * hypot(p[i].x - p[i+1].x, p[i].y - p[i+1].y);

				if (d < 1e-10)
					r[l1[i]][l2[j]] = 1;
			}
		}

		for (i = 0; i < m; i++)
			r[l2[i]][2] = 1;

		i = maxflow();
		printf("%d\n", n + 1 + i);

		for (i = 0; i < n; i++) {
			printf("%d %d ", p[i].x, p[i].y);

			for (j = 0; j < m; j++)
				if (r[l2[j]][l1[i]]) break;

			if (j < m)
				printf("%d %d ", q[j].x, q[j].y);
		}
		printf("%d %d\n", p[n].x, p[n].y);

		if (t > 0)
			printf("\n");
	}

	return 0;
}
