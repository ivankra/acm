#include <stdio.h>

int tab[1024][64];

void make()
{
	static int a[1024];
	int i, j, n, k;

	k = 2;
	a[0] = 2;
	a[1] = 3;

	for (n = 5; n <= 1000; n++) {
		for (i = 0; i < k; i++)
			tab[n][i] = a[i];
		tab[n][k] = 0;

		if (a[0] == 3) {
			if ((a[k - 1] - a[k - 2]) == 1) {
				a[k - 1]++;
				continue;
			}

			for (i = ++k; i > 0; i--)
				a[i] = a[i - 1];
			a[0] = 2;
			a[k - 1]--;
			continue;
		}

		for (i = k - 2; i >= 0; i--)
			if ((a[i + 1] - a[i]) > 1) break;

		if (i >= 0)
			a[i]++;
		else
			a[k - 1]++;
	}
}

int main()
{
	int i, n, t;

	for (make(), scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 0; tab[n][i]; i++)
			printf(i ? " %d" : "%d", tab[n][i]);
		printf(t ? "\n\n" : "\n");
	}

	return 0;
}
