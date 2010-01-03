#include <stdio.h>
#include <string.h>

struct {
	char s[128], r[16][5][128];
	int u, m;
} mta[16];

int n;

int get(char *r)
{
	int i;

	for (i = 0; i < n; i++)
		if (strcmp(mta[i].s, r) == 0) return i;

	return -1;
}

int solve()
{
	char s[5][128];
	int i, j, r;

	for (i = 0; i < 5; i++)
		scanf(" %s", s[i]);

	r = get(s[0]);
	if (r < 0)
		return printf("unable to route at %s\n", s[0]);

	for (i = 0; i < n; i++)
		mta[i].u = 0;

	for (;;) {
		if (mta[r].u++)
			return printf("circular routing detected by %s\n", mta[r].s);

		for (i = 0; i < mta[r].m; i++) {
			for (j = 1; j <= 4; j++)
				if (strcmp(mta[r].r[i][j], "*") != 0 &&
				    strcmp(mta[r].r[i][j], s[j]) != 0)
					break;
			if (j > 4) break;
		}

		if (i >= mta[r].m)
			return printf("unable to route at %s\n", mta[r].s);

		i = get(mta[r].r[i][0]);
		if (i < 0)
			return printf("unable to route at %s\n", mta[r].s);

		if (i == r)
			return printf("delivered to %s\n", mta[r].s);

		r = i;
	}
}

int main()
{
	int i, j, k, t;

	for (t = 1; scanf("%d", &n) == 1; t++) {
		printf("Scenario # %d\n", t);

		for (i = 0; i < n; i++) {
			scanf(" %s %d", mta[i].s, &mta[i].m);
			for (j = 0; j < mta[i].m; j++)
				for (k = 0; k < 5; k++)
					scanf(" %s", mta[i].r[j][k]);
		}

		for (scanf("%d", &k), i = 1; i <= k; i++) {
			printf("%d -- ", i);
			solve();
		}

		printf("\n");
	}

	return 0;
}
