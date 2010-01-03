#include <stdio.h>
#include <string.h>

#define SHIFT 4096

typedef struct {
	int m, diff, sum;
	unsigned a[8];
} jury_t;

jury_t list[163840], listnew[163840];
int tab[32][8192], count, m;

void add(int p, int d, int s)
{
	int i, j, k, r;

	for (i = 1, r = 0; i <= count; i++) {
		if (list[i].m >= m) continue;

		j = tab[list[i].m + 1][SHIFT + list[i].diff + d];
		if (j > 0 && list[j].sum >= (list[i].sum + s)) continue;

		listnew[r].m = list[i].m + 1;
		listnew[r].diff = list[i].diff + d;
		listnew[r].sum = list[i].sum + s;
		for (k = 0; k < 8; k++)
			listnew[r].a[k] = list[i].a[k];
		listnew[r].a[p >> 5] |= 1U << (p & 31);
		r++;
	}

	while (r-- > 0) {
		j = tab[listnew[r].m][SHIFT + listnew[r].diff];
		if (j > 0 && list[j].sum >= listnew[r].sum) continue;
		if (j == 0) j = ++count;
		memcpy(&list[j], &listnew[r], sizeof(jury_t));
		tab[list[j].m][SHIFT + list[j].diff] = j;
	}
}

int main()
{
	int i, j, n, t, x, y;

	for (t = 1; scanf("%d %d", &n, &m) == 2 && n > 0; t++) {
		printf("Jury #%d\n", t);

		memset(tab, 0, sizeof(tab));
		memset(list, 0, 2 * sizeof(jury_t));
		count = 1;

		for (i = 0; i < n && scanf("%d %d", &x, &y) == 2; i++)
			add(i, x - y, x + y);

		for (i = 0;; i++)
			if ((tab[m][SHIFT + i] | tab[m][SHIFT - i]) != 0) break;

		if (tab[m][SHIFT + i] != 0)
			j = tab[m][SHIFT + i];
		else
			j = tab[m][SHIFT - i];

		if (tab[m][SHIFT - i] != 0)
			if (list[tab[m][SHIFT - i]].sum > list[j].sum)
				j = tab[m][SHIFT - i];

		printf("Best jury has value %d for prosecution and value %d for defence:\n",
			(list[j].diff + list[j].sum) / 2,
			(list[j].sum - list[j].diff) / 2);

		for (i = 0; i < n; i++)
			if ((list[j].a[i >> 5] >> (i & 31)) & 1)
				printf(" %d", i + 1);
		printf("\n\n");
	}

	return 0;
}
