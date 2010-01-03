#include <stdio.h>
#include <string.h>

int tab[16][16][16], n, g;

int rec(int *s)
{
	int t[16], a[16], i;

	if (s[1] < 0)
		return (s[0] >= (n - g));

	for (i = 0; s[i] >= 0; i++)
		a[i] = 0;

	for (;;) {
		for (i = 0; s[i + 1] >= 0; i++)
			t[i] = tab[s[i]][s[i + 1]][a[i]];
		t[i] = -1;

		if (rec(t)) return 1;

		for (i = 0;; i++) {
			if (s[i + 1] < 0)
				return 0;
			else if (tab[s[i]][s[i + 1]][++a[i]] < 0)
				a[i] = 0;
			else
				break;
		}
	}
}

int solve(int *s)
{
	static int r[16][16], f[16][16];
	int i, j, k, m;

	memset(r, 0, sizeof(r));
	memset(f, 0, sizeof(f));

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; tab[i][j][k] >= 0; k++)
				r[i][j] |= 1 << tab[i][j][k];

	for (m = 0; s[m] >= 0; m++);

	for (i = 0; i < m; i++)
		f[m][i] |= 1 << s[i];

	while (m-- > 1) {
		for (k = 0; k < m; k++) {
			for (i = 0; i < n; i++) {
				if (((f[m + 1][k] >> i) & 1) == 0)
					continue;

				for (j = 0; j < n; j++)
					if (((f[m + 1][k + 1] >> j) & 1) == 1)
						f[m][k] |= r[i][j];
			}
		}
	}

	if ((f[1][0] >> (n - g)) == 0)
		return 0;

	return rec(s);
}

int main()
{
	char s[256];
	int a[256], i, j, k, t;

	for (t = 1; scanf("%d %d", &n, &g) == 2 && n > 0; t++) {
		printf("%sNTA %d\n", (t == 1) ? "" : "\n", t);

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				scanf(" %s", s);
				for (k = 0; s[k]; k++)
					tab[i][j][k] = s[k] - 'a';
				tab[i][j][k] = -1;
			}
		}

		while (scanf(" %s", s) == 1 && s[0] != '#') {
			for (i = 0; s[i]; i++)
				a[i] = s[i] - 'a';
			a[i] = -1;
			printf("%s %s\n", solve(a) ? "accept" : "reject", s);
		}
	}

	return 0;
}
