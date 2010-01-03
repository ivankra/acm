#include <stdio.h>

typedef struct { int a, b, c; } line_t;        /* ax + by + c = 0 */

line_t line(int x1, int y1, int x2, int y2)
{
	line_t l;
	l.a = y2 - y1;
	l.b = x1 - x2;
	l.c = (x2 - x1) * y1 + (y1 - y2) * x1;
	return l;
}

int main()
{
	int x1, y1, x2, y2, x3, y3, x4, y4, det, t;
	line_t l, m;

	printf("INTERSECTING LINES OUTPUT\n");
	for (scanf("%d", &t); t-- > 0;) {
		scanf("%d %d %d %d %d %d %d %d",
		      &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);

		l = line(x1, y1, x2, y2);
		m = line(x3, y3, x4, y4);

		det = l.a * m.b - l.b * m.a;

		if (det != 0)
			printf("POINT %.2lf %.2lf\n",
			       (double)(l.b * m.c - l.c * m.b) / (double)det,
			       (double)(l.c * m.a - l.a * m.c) / (double)det);
		else if (l.c * m.b == l.b * m.c && l.a * m.c == l.c * m.a)
			printf("LINE\n");
		else
			printf("NONE\n");
	}
	printf("END OF OUTPUT\n");

	return 0;
}
