#include <stdio.h>
#include <stdlib.h>

#define MAXN 10001

typedef struct {
	int x, z, idx, idz;
	char d;
} ant_t;

int cmpx(const void *p, const void *q)
{
	return (*(ant_t **)p)->x - (*(ant_t **)q)->x;
}

int cmpz(const void *p, const void *q)
{
	return (*(ant_t **)p)->z - (*(ant_t **)q)->z;
}

int main()
{
	static ant_t a[MAXN], *ax[MAXN], *az[MAXN];
	int i, z, n, tm, len, cn, cm;

	for (scanf("%d", &cm), cn = 1; cn <= cm && scanf("%d %d %d", &len, &tm, &n); cn++) {
		printf("Case #%d:\n", cn);

		for (i = 0; i < n && scanf("%d %c", &a[i].x, &a[i].d) == 2; i++) {
			a[i].z = a[i].x + ((a[i].d == 'R') ? tm : -tm);
			ax[i] = az[i] = &a[i];
		}

		qsort(ax, n, sizeof(ax[0]), &cmpx);
		qsort(az, n, sizeof(az[0]), &cmpz);

		for (i = 0; i < n; i++) {
			ax[i]->idx = i;
			az[i]->idz = i;
		}

		for (i = 0; i < n; i++) {
			z = az[a[i].idx]->z;
			if (z < 0 || z > len)
				printf("Fell off\n");
			else if ((a[i].idx > 0 && az[a[i].idx - 1]->z == z) ||
			         (a[i].idx < (n - 1) && az[a[i].idx + 1]->z == z))
				printf("%d Turning\n", z);
			else
				printf("%d %c\n", z, az[a[i].idx]->d);
		}

		printf("\n");
	}

	return 0;
}
