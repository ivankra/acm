#include <stdio.h>
#include <string.h>

struct { int dig[4], cnt[10], a, b; } g[16];
int ng;

static int check(int a)
{
	static int dig[4], cnt[10];
	register int i, j, k;

	for (i = 0; i < 10; i++)
		cnt[i] = 0;

	for (i = 0; i < 4; i++, a /= 10)
		cnt[dig[i] = a % 10]++;

	for (k = 0; k < ng; k++) {
		for (i = 0, j = 0; i < 4; i++)
			if (dig[i] == g[k].dig[i]) j++;
		if (j != g[k].a) return 0;


		for (i = 0, j = -g[k].a; i < 10; i++)
			j += (cnt[i] >= g[k].cnt[i]) ? g[k].cnt[i] : cnt[i];
		if (j != g[k].b) return 0;
	}

	return 1;
}

int main()
{
	int i, j, m, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &ng) == 1;) {
		memset(g, 0, sizeof(g));

		for (i = 0; i < ng; i++) {
			scanf("%d %d/%d", &m, &g[i].a, &g[i].b);
			for (j = 0; j < 4; j++, m /= 10)
				g[i].cnt[g[i].dig[j] = m % 10]++;
		}

		for (i = 0, j = 0, m = 0; i <= 9999; i++) {
			if (check(i)) {
				j = i;
				if (++m >= 2) break;
			}
		}

		if (m == 0)
			printf("impossible\n");
		else if (m == 1)
			printf("%.4d\n", j);
		else
			printf("indeterminate\n");
	}

	return 0;
}
