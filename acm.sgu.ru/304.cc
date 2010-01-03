#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 640
#define INF 0x3FFFFFFF

typedef struct {
	int cost, id;
} tooth_t;

int gum[MAX], cost[MAX][MAX], count[MAX], tab[MAX][MAX], tabbuy[MAX][MAX], k, n;
tooth_t list[MAX][MAX];

int res[MAX], nres;

/* cost[i][j] = mincost of buying j teeth at gum #i. */


int cmp(const void *pp, const void *qq)
{
	tooth_t *p = (tooth_t *)pp, *q = (tooth_t *)qq;
	return p->cost - q->cost;
}

int min(int a, int b) { return (a < b) ? a : b; }

int main()
{
	int i, j, buy, n, p, x, y;

/*	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
*/
	scanf("%d %d %d", &n, &k, &p);
	for (i = 1; i <= k; i++) scanf("%d", &gum[i]);

	memset(cost, 0, sizeof(cost));
	memset(count, 0, sizeof(count));

	for (i = 1; i <= n && scanf("%d %d", &x, &y) == 2; i++) {
		list[y][count[y]].cost = x;
		list[y][count[y]].id = i;
		count[y]++;
	}

	for (i = 1; i <= k; i++) {
		qsort(list[i], count[i], sizeof(tooth_t), &cmp);
		cost[i][0] = 0;
		for (j = 1; j <= count[i]; j++)
			cost[i][j] = cost[i][j-1] + list[i][j-1].cost;
		cost[i][count[i]+1] = -1;
	}

/*for(i=1;i<=k;i++) {printf("Gum %d:",i);for(j=0;j<=count[i];j++) printf(" %d", cost[i][j]);printf("\n");}
  */
	memset(tab, 0, sizeof(tab));
	memset(tabbuy, 0, sizeof(tabbuy));

	for (i = 0; i <= n; i++) tab[0][i] = INF; tab[0][0] = 0;

	for (i = 1; i <= k; i++) {
		for (j = 0; j <= n; j++)
			tab[i][j] = tab[i-1][j];

		for (buy = 1; buy <= count[i]; buy++) {
			for (j = buy; j <= n; j++) {
				x = tab[i-1][j-buy] + cost[i][buy] + gum[i];
				if (x >= tab[i][j]) continue;
				tab[i][j] = x; tabbuy[i][j] = buy;
			}


/*********/
if (tab[i][j] > p) break;
/********/

		}
	}
/*
printf("tab[k][0..n] = {");
for(i=0;i<=n;i++)printf(" %d:%d",tab[k][i],tabbuy[k][i]);printf(" }\n");
*/
	for (i = 0; i < n && tab[k][i+1] <= p; i++);

/*printf("result=%d   at the cost %d\n", i, tab[k][i]);*/
/*(k,i) -> (k-1, i - tabbuy[k][i]) */

	printf("%d\n", i);

	nres = 0;
	while (k > 0) {
		for (j = 0; j < tabbuy[k][i]; j++)
			res[nres++] = list[k][j].id;
		i -= tabbuy[k][i];
		k--;
	}

	for (i = 0; i < nres; i++)
		printf(i ? " %d" : "%d", res[i]);
	printf("\n");

	return 0;
}
