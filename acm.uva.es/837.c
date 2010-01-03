#include <stdio.h>
#include <stdlib.h>

typedef struct { double a, b, l; } seg_t;
seg_t s[131072];

int compare(const void *p, const void *q)
{
	return ((((seg_t *)p)->a < ((seg_t *)q)->a) ? -1 : 1);
}

int main()
{
	double a, b, r, t;
	int i, c, n, m;

	for (scanf("%d", &c); c-- > 0 && scanf("%d", &n) == 1;) {
		m = 1;
		s[0].a = -1. / 0.;
		s[0].b = 1. / 0.;
		s[0].l = 1.;

		while (n-- > 0 && scanf("%lf %*f %lf %*f %lf", &a, &b, &r) == 3) {
			if (a > b) {
				t = a;
				a = b;
				b = t;
			}


			for (i = m - 1; i >= 0; i--) {
				if (a < s[i].a && s[i].b < b) {
					s[i].l *= r;
				} else if (s[i].a < a && a < s[i].b &&
					   s[i].a < b && b < s[i].b) {
					s[m].a = a;
					s[m].b = b;
					s[m].l = s[i].l * r;
					m++;

					s[m].a = b;
					s[m].b = s[i].b;
					s[m].l = s[i].l;
					m++;

					s[i].b = a;

					break;
				} else if (s[i].a < a && a < s[i].b) {
					s[m].a = a;
					s[m].b = s[i].b;
					s[m].l = s[i].l * r;
					m++;
					s[i].b = a;
				} else if (s[i].a < b && b < s[i].b) {
					s[m].a = s[i].a;
					s[m].b = b;
					s[m].l = s[i].l * r;
					m++;
					s[i].a = b;
				}
			}
		}

		qsort(s, m, sizeof(s[0]), &compare);

		printf("%d\n", m);
		for (i = 0; i < m; i++) {
			printf(i ? "%.3f " : "-inf ", s[i].a);
			printf(((i + 1) < m) ? "%.3f " : "+inf ", s[i].b);
			printf("%.3f\n", s[i].l);
		}

		if (c > 0)
			printf("\n");
	}

	return 0;
}
