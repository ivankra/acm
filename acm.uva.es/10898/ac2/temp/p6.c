/* incorrect in general! */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 0x1FFFFFFF

typedef struct {
	int a[8], c;
} tup_t;

int cost[32], n, ntup, testid = 0;
tup_t tup[32];

int got[1048576], val[1048576];

int find(int a[], int s)
{
	int b[8], i, j, id;

	for (id = a[0], i = 1; i < n; i++)
		id = id * 10 + a[i];

	if (got[id] == testid)
		return val[id];

	got[id] = testid;

	if (id == 0)
		return val[id] = 0;

	for (val[id] = 0, i = 0; i < n; i++)
		val[id] += cost[i] * a[i];

	for (i = s; i < ntup; i++) {
		for (j = 0;; j++) {
			if (j < n) {
				b[j] = a[j] - tup[i].a[j];
				if (b[j] < 0) break;
			} else {
				j = tup[i].c + find(b,i);
				if (j < val[id]) val[id] = j;
				break;
			}
		}
	}

	return val[id];
}

int cmp(const void *p, const void *q)
{
	return ((tup_t *)p)->c - ((tup_t *)q)->c;
}

int main()
{
	int a[8], i, j, k, t;

	memset(got, 0, sizeof(got));

	while (scanf("%d", &n) == 1) {
		for (i = 0; i < n; i++)
			scanf("%d", &cost[i]);

		scanf("%d", &ntup);
		for (i = 0; i < ntup;) {
			for (j = 0; j < n; j++)
				scanf("%d", &tup[i].a[j]);
			scanf("%d", &tup[i].c);

			for (j = 0; j < n && tup[i].a[j] == 0; j++);
			if (j == n) { ntup--; continue; }

			for (k = 0, j = 0; j < n; j++)
				k += tup[i].a[j] * cost[j];
			if (k <= tup[i].c) { ntup--; continue; }

			i++;
		}

		qsort(tup, ntup, sizeof(tup[0]), &cmp);

		scanf("%d", &t);
		while (t-- > 0) {
			for (i = 0; i < n; i++)
				scanf("%d", &a[i]);
			testid++;
			printf("%d\n", find(a, 0));
		}
	}

	return 0;
}
