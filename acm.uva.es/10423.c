#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int t, id;
} sched_t;

sched_t s[1024];
int n;

int cmp(const void *p, const void *q)
{
	return ((sched_t *)p)->t - ((sched_t *)q)->t;
}

int main()
{
	int i, c, m, x, y;

	for (c = 1; scanf("%d", &m) == 1 && m > 0; c++) {
		for (n = 0; m-- > 0 && scanf("%d:", &x) == 1;) {
			while (scanf("%d", &y) == 1 && y >= 0) {
				s[n].t = y;
				s[n].id = x;
				n++;
			}
		}

		qsort(s, n, sizeof(s[0]), &cmp);

		scanf("%d %d", &x, &y);

		for (i = 0; i < n && s[i].t < x; i++);

		printf("Case %d: Peter arrives at stop %d by tram %d.\n",
			c, y, s[(i + y - 1) % n].id);
	}

	return 0;
}
