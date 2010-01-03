#include <stdio.h>

int main()
{
	static int pi[120][8], r[81], a[16], found;
	register int i, j, k, m;

	for (i = 0, k = 0, a[0] = -1; i >= 0;) {
		if (i == 5) {
			for (i = 0; i < 5; i++)
				pi[k][i] = a[i];
			k++;
			i = 4;
			continue;
		}

		while (++a[i] < 5) {
			for (j = 0; j < i; j++)
				if (a[j] == a[i]) break;

			if (j >= i)
				break;
		}

		if (a[i] < 5)
			a[++i] = -1;
		else
			i--;
	}

	while (scanf("%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4])==5) {
		if (a[0] == 0)
			break;

		for (m = 0, found = 0; !found && m < 120; m++) {
			r[0] = a[pi[m][0]];
			k = 1;

			for (j = 1; j <= 4; j++) {
				for (i = k; i-- > 0;) {
					r[k++] = r[i] + a[pi[m][j]];
					r[k++] = r[i] - a[pi[m][j]];
					r[i] *= a[pi[m][j]];
				}
			}

			for (i = 0; i < 81; i++)
				if (r[i] == 23) {
					found = 1;
					break;
				}
		}

		printf(found ? "Possible\n" : "Impossible\n");
	}

	return 0;
}
