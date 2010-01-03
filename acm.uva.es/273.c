#include <stdio.h>

typedef struct { int x1, y1, x2, y2; } seg_t;

int between(int a, int x, int b)
{
	if (a <= b)
		return (a <= x && x <= b);
	else
		return (b <= x && x <= a);
}

int isect(seg_t *s, seg_t *t)
{
	int sa, sb, sc, ta, tb, tc, d, x, y;

	sa = s->y1 - s->y2;
	sb = s->x2 - s->x1;
	sc = (s->y2 - s->y1) * s->x1 + (s->x1 - s->x2) * s->y1;

	ta = t->y1 - t->y2;
	tb = t->x2 - t->x1;
	tc = (t->y2 - t->y1) * t->x1 + (t->x1 - t->x2) * t->y1;

	d = sa * tb - sb * ta;
	if (d != 0) {
		x = sb * tc - sc * tb;
		y = sc * ta - sa * tc;
		return (between(s->x1 * d, x, s->x2 * d) &&
			between(s->y1 * d, y, s->y2 * d) &&
			between(t->x1 * d, x, t->x2 * d) &&
			between(t->y1 * d, y, t->y2 * d));
	}

	if ((sc * ta != sa * tc) || (sc * tb != sb * tc))
		return 0;

	return (between(s->x1, t->x1, s->x2) || between(s->x1, t->x2, s->x2) ||
		between(t->x1, s->x1, t->x2) || between(t->x1, s->x2, t->x2));
}

int main()
{
	static int c[16][16], n, t, x, y;
	static seg_t s[16];
	int i, j, k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 1; i <= n; i++)
			scanf("%d %d %d %d",
			      &s[i].x1, &s[i].y1, &s[i].x2, &s[i].y2);

		for (i = 1; i <= n; i++)
			for (c[i][i] = 1, j = i + 1; j <= n; j++)
				c[i][j] = c[j][i] = isect(&s[i], &s[j]);

		for (k = 1; k <= n; k++)
			for (i = 1; i <= n; i++)
				if (c[i][k])
					for (j = 1; j <= n; j++)
						c[i][j] |= c[k][j];

		while (scanf("%d %d", &x, &y) == 2 && x != 0)
			printf(c[x][y] ? "CONNECTED\n" : "NOT CONNECTED\n");

		if (t > 0)
			printf("\n");
	}

	return 0;
}
