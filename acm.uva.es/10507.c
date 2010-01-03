#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get()
{
	int c;
	while ((c = getchar()) != EOF && !isalpha(c));
	return (c == EOF) ? EOF : (toupper(c) - 'A');
}

int main()
{
	static int a[32], d[32][32], m, n, r;
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		memset(a, 0, sizeof(a));
		for (i = 0; i < 3; i++)
			a[get()] = 1;

		memset(d, 0, sizeof(d));
		while (m-- > 0) {
			i = get();
			j = get();
			d[i][j] = d[j][i] = 1;
		}

		for (m = 1;; m++) {
			for (i = r = 0; i < 26; i++) {
				if (a[i]) continue;

				for (j = k = 0; j < 26; j++)
					if (d[i][j] && 0 < a[j] && a[j] <= m)
						k++;

				if (k >= 3) {
					a[i] = m + 1;
					r++;
				}
			}

			if (r == 0) break;
		}

		for (i = k = 0; i < 26; i++)
			if (a[i]) k++;

		if (k < n)
			printf("THIS BRAIN NEVER WAKES UP\n");
		else
			printf("WAKE UP IN, %d, YEARS\n", m - 1);
	}	

	return 0;
}
