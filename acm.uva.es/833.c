#include <stdio.h>
#include <assert.h>

typedef struct { int x1, y1, x2, y2; } line;	/* y1 > y2 */

line l[65536];
int n;

int solve(int x, int y)
{
	int i, j, p, q, u, v;

	for (;;) {
		if (y <= 0) return x;

		for (p = q = i = 0, j = -1; i < n; i++) {
			if (l[i].y2 >= y || x == l[i].x1 || x == l[i].x2)
				continue;

			if (x < l[i].x1 && x < l[i].x2)
				continue;

			if (x > l[i].x1 && x > l[i].x2)
				continue;

			v = l[i].x1 - l[i].x2;
			u = l[i].y1 * v + (l[i].y1 - l[i].y2) * (x - l[i].x1);

			if (j < 0 || (u * q) > (p * v))
				p = u, q = v, j = i;
		}

		if (j < 0)
			return x;

		x = l[j].x2;
		y = l[j].y2;
	}
}

int main()
{
	int i, m, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; i < n; i++) {
			scanf("%d %d %d %d", &l[i].x1, &l[i].y1, &l[i].x2, &l[i].y2);
			if (l[i].x1 == l[i].x2 || l[i].y1 == l[i].y2) {
				i--; n--;
				continue;
			}

			if (l[i].y1 < l[i].y2) {
				m = l[i].y1; l[i].y1 = l[i].y2; l[i].y2 = m;
				m = l[i].x1; l[i].x1 = l[i].x2; l[i].x2 = m;
			}

			if (l[i].y1 <= 0) {
				i--; n--;
				continue;
			}

			assert(l[i].y2 >= 0);
		}

		for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x, &y) == 2;)
			printf("%d\n", solve(x, y));

		if (t) printf("\n");
	}

	return 0;
}
