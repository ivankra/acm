#include <stdio.h>
#include <string.h>

static int g_buf[128][128], *g_tab[32768], g_tab_n;
static int f_buf1[128], f_buf2[128];

int main()
{
	static int gt[128], gp[128], gs[128], np, p, n, t, k;
	int i, j, m, s, *tab, *next;

	scanf("%d", &np);
	for (p = 1; p <= np && scanf("%d %d %d", &n, &k, &t) == 3; p++) {
		if (p != 1)
			printf("\n");

		for (g_tab_n = 0, i = 0; i <= t; i++)
			g_tab[i] = NULL;

		for (i = 0; i < n; i++)
			scanf("%d", &gt[i]);

		for (i = 0; i < n; i++)
			scanf("%d", &gp[i]);

		for (i = 0; i < n; i++)
			scanf("%d", &gs[i]);

		if (k == 0) {
			printf("0\n");
			continue;
		}

		if (k == 1) {
			for (i = 0, j = 0; i < n; i++)
				if (gt[i] > 0) j += gp[i];
			printf("%d\n", j);
			continue;
		}

		for (i = 0; i < n; i++) {
			if (g_tab[gt[i]] == NULL) {
				g_tab[gt[i]] = g_buf[g_tab_n++];
				memset(g_tab[gt[i]], 0, (k + 2) * sizeof(int));
			}

			g_tab[gt[i]][gs[i]] += gp[i];
		}

		tab = f_buf1;
		next = f_buf2;

		for (tab[0] = 0, i = 1; i <= k; i++)
			tab[i] = -1;
		tab[k + 1] = -1;

		for (m = 1; m <= t; m++) {
			next[k + 1] = -1;
			for (i = 0; i <= k; i++) {
				next[i] = -1;

				for (j = (i > 0) ? -1 : 0; j <= 1; j++) {
					if (tab[i + j] < 0)
						continue;

					s = tab[i + j];
					if (g_tab[m])
						s += g_tab[m][i];

					if (s > next[i])
						next[i] = s;
				}
			}

			tab = next;
			next = (next == f_buf1) ? f_buf2 : f_buf1;
		}

		for (j = tab[0], i = 1; i <= k; i++)
			if (tab[i] > j) j = tab[i];

		printf("%d\n", j);
	}

	return 0;
}
