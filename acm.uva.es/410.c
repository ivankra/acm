#include <stdio.h>
#include <string.h>

static struct {
	int n[8], a[8][2], r;
} sol, best;

static int c, s, val[16], total, use[16], left;

static void solve(int p)
{
	int i, j, k;

	if (sol.r >= best.r)
		return;

	if (p == 0) {
		if (left > 2)
			return;

		sol.n[0] = left;
		for (i = 0, j = 0; i < s; i++)
			if (use[i] == 0) sol.a[0][j++] = val[i];

		for (i = 0, j = 0; i < left; i++)
			j += sol.a[0][i];

		j = c * j - total;
		if (j < 0) j = -j;

		sol.r += j;

		if (sol.r < best.r)
			memcpy(&best, &sol, sizeof(sol));

		sol.r -= j;

		return;
	}

	if (left > ((p + 1) * 2))
		return;

	sol.n[p] = 0;
	sol.r += total;
	solve(p - 1);
	sol.r -= total;

	if (left < 1)
		return;

	sol.n[p] = 1;
	left--;
	for (i = s - 1; i >= 0; i--) {
		if (use[i]) continue;
		sol.a[p][0] = val[i];

		k = c * val[i] - total;
		if (k < 0) k = -k;

		sol.r += k;

		use[i] = 1;
		solve(p - 1);
		use[i] = 0;

		sol.r -= k;
	}
	left++;

	if (left < 2)
		return;

	sol.n[p] = 2;
	left -= 2;
	for (i = s - 1; i >= 0; i--) {
		if (use[i]) continue;

		use[i] = 1;
		sol.a[p][1] = val[i];
		for (j = i - 1; j >= 0; j--) {
			if (use[j]) continue;
			use[j] = 1;
			sol.a[p][0] = val[j];

			k = c * (val[i] + val[j]) - total;
			if (k < 0) k = -k;

			sol.r += k;

			solve(p - 1);

			sol.r -= k;
			use[j] = 0;
		}
		use[i] = 0;
	}
	left += 2;
}

int main()
{
	int i, j, t;

	for (t = 1; scanf("%d %d", &c, &s) == 2 && c > 0; t++) {
		for (i = 0; i < s; i++)
			scanf("%d", &val[i]);

		memset(use, 0, sizeof(use));

		memset(&sol, 0, sizeof(sol));
		memset(&best, 0, sizeof(best));
		best.r = 0x3FFFFFFF;
		left = s;

		for (i = 0, total = 0; i < s; i++)
			total += val[i];

		printf("Set #%d\n", t);
		solve(c - 1);

		for (i = 0; i < c; i++) {
			printf(" %d:", i);
			for (j = 0; j < best.n[i]; j++)
				printf(" %d", best.a[i][j]);
			printf("\n");
		}
		printf("IMBALANCE = %.5f\n\n", (double)best.r / (double)c);
	}

	return 0;
}
