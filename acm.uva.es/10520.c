#include <stdio.h>
#include <string.h>

typedef unsigned long long ull;

static int n, an1;
static ull tab[512][512];
static char found[512][512];

static ull f(int i, int j)
{
	int k;
	ull m, s, t;

	if (found[i][j])
		return tab[i][j];

	if (i < j) {
		for (k = i; k < j; k++) {
			t = f(i, k) + f(k + 1, j);
			if (k == i || t > m) m = t;
		}

		found[i][j] = 1;
		return (tab[i][j] = m);
	}

	if (i < n) {
		for (k = i + 1; k <= n; k++) {
			t = f(k, 1) + f(k, j);
			if (k == (i + 1) || t > s) s = t;
		}
	} else {
		s = 0;
	}

	if (j > 1) {
		for (k = 1; k < j; k++) {
			t = f(i, k) + f(n, k);
			if (k == 1 || t > m) m = t;
		}
	} else {
		m = 0;
	}

	found[i][j] = 1;
	return (tab[i][j] = (m + s));
}

int main()
{
	int t, s;

	while (scanf("%d %d", &n, &an1) == 2) {
		memset(found, 0, sizeof(found));

		found[n][1] = 1;
		tab[n][1] = an1;

		printf("%lld\n", f(1, n));
	}

	return 0;
}
