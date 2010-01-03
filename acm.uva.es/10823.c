#include <stdio.h>

struct {
	int type, px, py, len, rad2, r, g, b;
} obj[128];
int n;

void sol(int x, int y)
{
	int i, d, r, g, b, k;

	r = g = b = 0;
	k = 0;

	for (i = 0; i < n; i++) {
		if (obj[i].type == 's') {
			if (x < obj[i].px || x > (obj[i].px + obj[i].len) ||
			    y < obj[i].py || y > (obj[i].py + obj[i].len))
				continue;

			if (x == obj[i].px || x == (obj[i].px + obj[i].len) ||
			    y == obj[i].py || y == (obj[i].py + obj[i].len)) {
				printf("(0, 0, 0)\n");
				return;
			}

			k++;
			r += obj[i].r;
			g += obj[i].g;
			b += obj[i].b;
		} else {
			d = ((x - obj[i].px) * (x - obj[i].px) +
			     (y - obj[i].py) * (y - obj[i].py));

			if (d > obj[i].rad2)
				continue;

			if (d == obj[i].rad2) {
				printf("(0, 0, 0)\n");
				return;
			}

			k++;
			r += obj[i].r;
			g += obj[i].g;
			b += obj[i].b;
		}
	}

	if (k == 0) {
		printf("(255, 255, 255)\n");
		return;
	}

#define ROUND(p,q) ((int)((((double)(p)) / ((double)(q))) + 0.5 + 10e-9))

	r = ROUND(r, k);
	g = ROUND(g, k);
	b = ROUND(b, k);

	printf("(%d, %d, %d)\n", r, g, b);
}

int main()
{
	char s[128];
	int i, c, t, p, x, y;

	for (scanf("%d", &t), c = 0; c++ < t && scanf("%d %d", &n, &p) == 2;) {
		for (i = 0; i < n; i++) {
			scanf(" %[A-Za-z] %d %d %d %d %d %d",
			      s, &obj[i].px, &obj[i].py, &obj[i].len,
			      &obj[i].r, &obj[i].g, &obj[i].b);

			if (s[0] == 'C' || s[0] == 'c') {
				obj[i].type = 'c';
				obj[i].rad2 = obj[i].len * obj[i].len;
			} else {
				obj[i].type = 's';
			}
		}

		printf("%sCase %d:\n", (c == 1) ? "" : "\n", c);

		while (p-- && scanf("%d %d", &x, &y) == 2)
			sol(x, y);
	}

	return 0;
}
