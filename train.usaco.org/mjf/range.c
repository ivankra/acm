/*
ID: mjf28791
PROG: range
LANG: C
*/
#include <stdio.h>

int above[256], count[256], n;

int main()
{
	int r, i, j, k;

	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		count[i] = above[i] = 0;

	for (r = 0; r < n; r++) {
		for (i = 0; i < n && (j = getchar()) != EOF;)
			if (j == '0')
				above[i++] = 0;
			else if (j == '1')
				above[i++]++;

		for (i = 0; i < n; i++) {
			for (j = i + 1, k = above[i]; j <= n; j++) {
				if (k >= (j - i))
					count[j - i]++;
				else
					break;

				if (j < n && above[j] < k)
					k = above[j];
			}
		}
	}

	for (i = 2; i <= n; i++)
		if (count[i]) printf("%d %d\n", i, count[i]);

	return 0;
}
