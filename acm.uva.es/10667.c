#include <stdio.h>

int main()
{
	static int a[128][128], d[128], n, b, t, r, r1, r2, c1, c2, result;
	int i, j, k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &b) == 2;) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				a[i][j] = 0;

		while (b-- > 0 && scanf("%d %d %d %d",&r1,&c1,&r2,&c2) == 4)
			for (i = r1 - 1, c1--; i < r2; i++)
				for (j = c1; j < c2; j++)
					a[i][j] = 1;

		for (i = 0; i < n; i++)
			d[i] = 0;

		for (result = 0, r = 0; r < n; r++) {
			for (i = 0; i < n; i++)
				if (a[r][i])
					d[i] = 0;
				else
					d[i]++;

			for (i = 0; i < n; i++) {
				for (j = i + 1, k = d[i];; j++) {
					if ((k * (j - i)) > result)
						result = k * (j - i);

					if (j >= n)
						break;
					else if (d[j] < k)
						k = d[j];
				}
			}
		}

		printf("%d\n", result);
	}

	return 0;
}
