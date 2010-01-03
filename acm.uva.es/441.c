#include <stdio.h>

static int a[16], c[16], i, j, k, t;

int main()
{
	for (t = 0; scanf("%d", &k) == 1 && k > 0; t++) {
		if (t != 0)
			printf("\n");

		for (i = 0; i < k; i++)
			scanf("%d", &a[i]);

		for (i = 0, c[0] = -1; i >= 0;) {
			if (i == 6) {
				for (j = 0; j < 6; j++)
					printf((j==5)?"%d\n":"%d ", a[c[j]]);
				i--;
			} else if (++c[i] >= k) {
				i--;
			} else {
				c[i + 1] = c[i];
				i++;
			}
		}
	}
	return 0;
}
