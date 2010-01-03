#include <stdio.h>

static int solve(int n[])
{
	static int tab[8][65536];
	int i, j, k, s;

	for (s = 0, i = 1; i <= 6; i++)
		s += i * n[i];

	if ((s % 2) != 0)
		return 0;

	s /= 2;

	for (i = 0; i <= n[1]; i++)
		tab[1][i] = 1;

	for (; i <= s; i++)
		tab[1][i] = 0;

	for (k = 2; k <= 6; k++) {
		for (i = 0; i < k; i++)
			tab[k][i] = tab[k - 1][i];

		for (i = k; i <= s; i++) {
			tab[k][i] = tab[k][i - k] + tab[k - 1][i];
			if ((i - k * (n[k] + 1)) >= 0)
				tab[k][i] -= tab[k - 1][i - k * (n[k] + 1)];
		}
	}

	return tab[6][s] ? 1 : 0;
}

int main()
{
	int n[8], s, t, i;

	for (t = 1;; t++) {
		for (i = 1, s = 0; i <= 6 && scanf("%d", &n[i]) == 1; i++)
			s += n[i];

		if (i <= 6 || s == 0)
			break;

		printf("Collection #%d:\n%s be divided.\n\n",
			t, solve(n) ? "Can" : "Can't");
	}

	return 0;
}
