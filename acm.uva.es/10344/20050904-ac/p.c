#include <stdio.h>
#include <stdlib.h>

int pi[120][8], a[8], r[256];

void make()
{
	int i, j, k, t, n = 5;
	
	for (i = 0; i < n; i++)
		pi[0][i] = i;

	for (k = 1;; k++) {
		for (j = n - 2; j >= 0 && pi[k-1][j] > pi[k-1][j+1]; j--);
		if (j < 0) break;

		for (i = 0; i < n; i++)
			pi[k][i] = pi[k - 1][i];

		for (i = n - 1; pi[k][i] < pi[k][j]; i--);

		t = pi[k][i], pi[k][i] = pi[k][j], pi[k][j] = t;
		for (j++, i = n - 1; j < i;)
			t = pi[k][j], pi[k][j++] = pi[k][i], pi[k][i--] = t;
	}
}

int main()
{
	int i, j, k, p;

	make();

	for (;;) {
		for (i = j = 0; i < 5 && scanf("%d", &a[i]) == 1; i++)
			if (a[i] != 0) j = 1;
		if (i < 5 || j == 0) break;

		for (p = 0; p < 120; p++) {
			for (r[0] = a[pi[p][0]], k = 1, i = 1; i <= 4; i++) {
				for (j = k; j--;) {
					r[k++] = r[j] + a[pi[p][i]];
					r[k++] = r[j] - a[pi[p][i]];
					r[j] *= a[pi[p][i]];
				}
			}

			while (k-- && abs(r[k]) != 23);
			if (k > 0) break;
		}

		printf((p < 120) ? "Possible\n" : "Impossible\n");
	}

	return 0;
}
