/* .016 */
#include <stdio.h>
#include <string.h>

#define INF 0x1FFFFFFF

typedef struct {
	int a[8], c;
} tup_t;

int cost[32], n, ntup, testid = 0;
tup_t tup[32];

int got[1048576], val[1048576];

int find(int a[])
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

	for (i = 0; i < ntup; i++) {
		for (j = 0;; j++) {
			if (j < n) {
				b[j] = a[j] - tup[i].a[j];
				if (b[j] < 0) break;
			} else {
				j = tup[i].c + find(b);
				if (j < val[id]) val[id] = j;
				break;
			}
		}
	}

	return val[id];
}

int main()
{
	int a[8], i, j, t;

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
			if (j == n) ntup--; else i++;
		}

		scanf("%d", &t);
		while (t-- > 0) {
			for (i = 0; i < n; i++)
				scanf("%d", &a[i]);
			testid++;
			printf("%d\n", find(a));
		}
	}

	return 0;
}
