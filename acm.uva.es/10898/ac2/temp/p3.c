/* .273 */
/* possibly incorrect in general! */
#include <stdio.h>
#include <string.h>

#define INF 0x1FFFFFFF

int n, m, testno;
int tup[32][8], cost[32];

int got[1048576], val[1048576];

int find(int a[], int s)
{
	int b[8], i, j, id;

	for (id = a[0], i = 1; i < n; i++)
		id = id * 10 + a[i];

	if (got[id] == testno)
		return val[id];

	got[id] = testno;

	if (id == 0)
		return val[id] = 0;

	val[id] = INF;
	for (i = s; i < m; i++) {
		for (j = 0; j < n; j++) {
			b[j] = a[j] - tup[i][j];
			if (b[j] < 0) goto next;
		}

		j = cost[i] + find(b, i);
		if (j < val[id]) val[id] = j;
next: ;
	}

	return val[id];
}

int main()
{
	int a[16], i, j, t;

	memset(got, 0, sizeof(got));

	for (testno = 1; scanf("%d", &n) == 1; testno++) {
		memset(tup, 0, sizeof(tup));

		for (i = 0; i < n; i++) {
			scanf("%d", &cost[i]);
			tup[i][i] = 1;
		}

		scanf("%d", &m);
		m += n;

		for (i = n; i < m;) {
			for (j = 0; j < n; j++) scanf("%d", &tup[i][j]);
			scanf("%d", &cost[i]);

			for (j = 0; j < n && tup[i][j] == 0; j++);
			if (j == n) m--; else i++;
		}

/*		for (i = 0; i < m; i++) {
			printf("(");
			for(j=0;j<n;j++)printf(" %d",tup[i][j]);printf(" ), %d\n", cost[i]);
		}
		printf("\n");
*/

		scanf("%d", &t);
		while (t-- > 0) {
			for (i = 0; i < n; i++) scanf("%d", &a[i]);
			printf("%d\n", find(a,0));
testno++;
		}
	}

	return 0;
}
