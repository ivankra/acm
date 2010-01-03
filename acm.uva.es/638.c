#include <stdio.h>
#include <stdlib.h>

struct rec_t {
	char l;
	int x, y;
} r[256];

int n;

int cmp(const void *p, const void *q)
{
	return (int)((struct rec_t *)p)->l - (int)((struct rec_t *)q)->l;
}

void solve()
{
	int a, b, c, d, k = 0;

	for (a = 0; a < n; a++) {
		for (b = 0; b < n; b++) {
			if (r[b].y != r[a].y || r[b].x <= r[a].x) continue;

			for (c = 0; c < n; c++) {
				if (r[c].x != r[b].x || r[c].y >= r[b].y) continue;

				for (d = 0; d < n; d++) {
					if (r[d].x != r[a].x || r[d].y != r[c].y)
						continue;

					printf("%s%c%c%c%c",
						(k++ % 10) ? " " : "\n ",
						r[a].l, r[b].l, r[c].l, r[d].l);
				}
			}
		}
	}

	printf(k ? "\n" : " No rectangles\n");
}

int main()
{
	int i, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf(" %c %d %d", &r[i].l, &r[i].x, &r[i].y);
		qsort(r, n, sizeof(r[0]), &cmp);

		printf("Point set %d:", t);
		solve();
	}

	return 0;
}
