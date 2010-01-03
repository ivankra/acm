#include <stdio.h>

typedef struct {
	int x, y;
	char s[4];
} pt;

int area(pt a, pt b, pt c)
{
	int s;
	s = (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
	return ((s < 0) ? -s : s);
}

int inside(pt z, pt a, pt b, pt c)
{
	return ((area(z,a,b) + area(z,b,c) + area(z,a,c)) == area(a,b,c));
}

int main()
{
	static pt p[128];
	static char s[16];
	int a, b, c, i, n, m;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf(" %[A-Za-z] %d %d", p[i].s, &p[i].x, &p[i].y);

		for (a = 0, m = -1, s[0] = '\0'; a < n; a++) {
			for (b = a + 1; b < n; b++) {
				for (c = b + 1; c < n; c++) {
					if (area(p[a], p[b], p[c]) <= m)
						continue;

					for (i = 0; i < n; i++)
						if (i != a && i != b && i != c &&
						    inside(p[i],p[a],p[b],p[c]))
							break;

					if (i < n)
						continue;

					m = area(p[a], p[b], p[c]);
					sprintf(s, "%s%s%s",
						p[a].s, p[b].s, p[c].s);
				}
			}
		}

		for (a = 1; a < 3; a++) {
			for (b = s[a], i = a - 1; i >= 0 && s[i] > b; i--)
				s[i + 1] = s[i];
			s[i + 1] = b;
		}

		printf("%s\n", s);
	}

	return 0;
}
