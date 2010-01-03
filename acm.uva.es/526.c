#include <stdio.h>
#include <string.h>

static int min(int a, int b)
{
	return (a < b) ? a : b;
}

int main()
{
	static int d[128][128], n, m, c, t;
	static char s1[128], s2[128];
	int i, j, k;

	for (t = 0; gets(s1) && gets(s2); t++) {
		if (t != 0)
			printf("\n");

		m = strlen(s1);
		n = strlen(s2);

		for (i = 0; i <= n; i++)
			d[m][i] = n - i;

		for (i = 0; i <= m; i++)
			d[i][n] = m - i;

		for (i = m - 1; i >= 0; i--) {
			for (j = n - 1; j >= 0; j--) {
				if (s1[i] == s2[j]) {
					d[i][j] = d[i + 1][j + 1];
					continue;
				}

				d[i][j] = min(d[i+1][j+1], min(d[i+1][j], d[i][j+1])) + 1;
			}
		}

		printf("%d\n", d[0][0]);

		for (i = j = k = c = 0; i < m && j < n;) {
			if (s1[i] == s2[j]) {
				i++;
				j++;
				k++;
			} else if (d[i+1][j+1] <= min(d[i+1][j], d[i][j+1])) {
				printf("%d Replace %d,%c\n", ++c, k+1, s2[j]);
				i++;
				k++;
				j++;
			} else if (d[i+1][j] <= d[i][j+1]) {
				printf("%d Delete %d\n", ++c, k+1);
				i++;
			} else {
				printf("%d Insert %d,%c\n", ++c, k+1, s2[j]);
				k++;
				j++;
			}
		}

		for (; i < m; i++)
			printf("%d Delete %d\n", ++c, k + 1);

		while (j < n)
			printf("%d Insert %d,%c\n", ++c, ++k, s2[j++]);

	}

	return 0;
}
