#include <stdio.h>
#include <stdlib.h>

int lev[1024], cnt[1024], cum[1024], n, total;

void solve(int x)
{
	int i, j, w;

	for (w = lev[i = 0], j = 0; x > 0; i++) {
		if ((i + 1) >= n || ((lev[i + 1] - w) * cum[i] * 100) > x) break;
		x -= (lev[i + 1] - w) * cum[i] * 100;
		w = lev[i + 1];
		j += cnt[i];
	}

	if (x == 0) {
		printf("Water level is %d.00 meters.\n"
		       "%.2f percent of the region is under water.\n\n",
		       w, (double)j * 100. / (double)total);
	} else {
		printf("Water level is %.2f meters.\n"
		       "%.2f percent of the region is under water.\n\n",
		       (double)(w + x / (cum[i] * 100.)),
		       (double)cum[i] * 100. / (double)total);
	}
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int main()
{
	int i, j, t, r, c;

	for (t = 1; scanf("%d %d", &r, &c) == 2 && (r != 0 || c != 0); t++) {
		total = r * c;
		for (i = 0, j = 0; i < total; i++)
			scanf("%d", &lev[j++]);
		scanf("%d", &r);

		qsort(lev, j, sizeof(lev[0]), &cmp);

		for (i = n = 0; i < j; i++) {
			if (i == 0 || lev[i - 1] != lev[i]) {
				lev[n] = lev[i];
				cnt[n] = 1;
				n++;
			} else {
				cnt[n - 1]++;
			}
		}

		for (cum[0] = cnt[0], i = 1; i < n; i++)
			cum[i] = cum[i - 1] + cnt[i];

		printf("Region %d\n", t);
		solve(r);
	}

	return 0;
}
