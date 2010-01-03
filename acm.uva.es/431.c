#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int score[128], cost[128], cap, n;
char name[128][128];

int cmp(const void *p, const void *q)
{
	int a = *(int *)p, b = *(int *)q;
	if (cost[a] != cost[b]) return (cost[a] - cost[b]);
	if (score[a] != score[b]) return (score[b] - score[a]);
	return strcmp(name[a], name[b]);
}

void solve()
{
	static unsigned choice[256][4];
	static int tab[256], tabcost[256], r[128];
	int i, j, k, t;

	for (i = 0; i < n && cost[i] > cap; i++);

	if (i >= n) {
		printf("There is not enough time to present any evidence. Drop the charges.\n");
		return;
	}

	memset(tab, 0, sizeof(tab));
	memset(tabcost, 0, sizeof(tabcost));
	memset(choice, 0, sizeof(choice));

	for (k = 0; k < n; k++) {
		for (i = cap, j = cap - cost[k]; j >= 0; i--, j--) {
			t = tab[j] + score[k];

			if (t < tab[i] ||
			    (t == tab[i] && (tabcost[j] + cost[k]) >= tabcost[i]))
				continue;

			tab[i] = t;
			tabcost[i] = tabcost[j] + cost[k];
			choice[i][0] = choice[j][0];
			choice[i][1] = choice[j][1];
			choice[i][2] = choice[j][2];
			choice[i][3] = choice[j][3];
			choice[i][k >> 5] |= 1U << (k & 31);
		}
	}

	for (i = k = 0; i < n; i++)
		if ((choice[cap][i >> 5] >> (i & 31)) & 1) r[k++] = i;

	qsort(r, k, sizeof(int), &cmp);

	printf("Score  Time  Description\n-----  ----  -----------\n");

	for (i = 0; i < k; i++)
		printf("%3d%7d   %s\n", score[r[i]], cost[r[i]], name[r[i]]);

	printf("\nTotal score: %d points\n Total time: %d hours\n",
		tab[cap], tabcost[cap]);
}

int main()
{
	static char buf[1024];
	int i, t;

	for (scanf("%d", &t); t-- > 0;) {
		while (gets(buf) && sscanf(buf, "%d", &cap) != 1);

		for (i = 0; i < 128; i++)
			name[i][0] = '\0';

		for (n = 0; gets(buf) && sscanf(buf, "%d %d %[^\n]", &score[n], &cost[n], name[n]) >= 2; n++);

		solve();

		if (t > 0) printf("\n");
	}

	return 0;
}
