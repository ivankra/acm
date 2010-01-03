#include <stdio.h>

#define INF 0x3FFFFFFF

static int t[1024], cum[1024], cov[1024], di[1024], m, n, len, c, s;
static int total1[1024], total2[1024];

int main()
{
	int i, j, k, r, *total, *next;

	for (di[0] = 0, i = 1; i < 1000; i++)
		di[10 + i] = i * i;

	for (s = 1; scanf("%d %d %d", &n, &len, &c) == 3 && n > 0; s++) {
		for (i = 1; i <= n; i++)
			scanf("%d", &t[i]);

		for (i = 1; i <= 10; i++)
			di[i] = -c;

		for (cum[0] = 0, i = 1; i <= n; i++)
			cum[i] = cum[i - 1] + t[i];

		for (i = 1; i <= n; i++) {
			for (j = i; j <= n; j++)
				if ((cum[j] - cum[i - 1]) > len) break;
			cov[i] = j - i;
		}

		for (i = 1, m = 0; i <= n; i += cov[i], m++);

		total = total1;
		next = total2;

		for (i = 0; i <= n; i++)
			total[i] = INF;
		total[n + 1] = 0;

		for (k = 1; k <= m; k++) {
			for (i = 1; i <= n; i++) {
				next[i] = INF;
				for (j = 1; j <= cov[i]; j++) {
					r = di[len - cum[i+j-1] + cum[i-1]] +
					    total[i + j];

					if (r < next[i])
						next[i] = r;
				}
			}

			total = next;
			next = (next == total1) ? total2 : total1;
		}

		printf(
			"%sCase %d:\n"
			"Minimum number of lectures: %d\n"
			"Total dissatisfaction index: %d\n",
			(s == 1) ? "" : "\n", s,
			m, total[1]
		);
	}

	return 0;
}
