#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	static int a[3][32], n[3], t;
	int i, j, k;

	for (scanf("%d", &t); t-- > 0 && scanf("%d%d%d", &n[0], &n[1], &n[2]) == 3;) {
		memset(a, 0, sizeof(a));
		for (i = 0; i < 3; i++)
			for (j = 0; j < n[i] && (k = getchar()) != EOF;)
				if (isalpha(k)) a[i][k - 'A']++, j++;

		for (j = 0, i = 0; i < 26; i++)
			j += a[0][i] * a[1][i] * a[2][i];

		printf("%.4f\n", 34. * j / (double)(n[0] * n[1] * n[2]));
	}

	return 0;
}
