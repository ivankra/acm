#include <stdio.h>
#include <string.h>

int main()
{
	static int a[128], n, m, r;
	int i, j, k;

	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		memset(a, 0, sizeof(a));

		for (r = 0; n-- > 0;) {
			for (i = 0; i < m && (k = getchar()) != EOF;)
				if (k == '0')
					a[i++] = 0;
				else if (k == '1')
					a[i++]++;

			for (i = 0; i < m; i++) {
				for (k = a[i], j = i; a[j] > 0; j++) {
					if (a[j] < k) k = a[j];
					r += k;
				}
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
