#include <stdio.h>
#include <string.h>

int main()
{
	static double a[32][32], r;
	static char names[32][256], s1[256], s2[256];
	int i, j, k, m, n, t;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++)
			scanf(" %[^ \t\r\n]", names[i]);

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				a[i][j] = 0.;
			a[i][i] = 1.;
		}

		for (scanf("%d", &m); m-- > 0;) {
			scanf(" %[^ \t\r\n] %lf %[^ \t\r\n]", s1, &r, s2);

			for (i = 0; i < n && strcmp(names[i], s1) != 0; i++);
			for (j = 0; j < n && strcmp(names[j], s2) != 0; j++);
		
			a[i][j] = r;
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (a[i][k] == 0.) continue;
				for (j = 0; j < n; j++) {
					if ((a[i][k] * a[k][j]) <= a[i][j])
						continue;
					a[i][j] = a[i][k] * a[k][j];
				}
				if (a[i][i] > (1. + 1e-9)) break;
			}
			if (i < n) break;
		}

		printf("Case %d: %s\n", t, (k < n) ? "Yes" : "No");
	}

	return 0;
}
