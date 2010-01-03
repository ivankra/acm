#include <stdio.h>
#include <string.h>

int main()
{
	static char m[16384];
	static int a[16384], n;
	register int i, j, k;

	while (scanf("%d :", &n) > 0 && n > 1) {
		memset(m, '\0', n + 1);

		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);

		m[a[0]] = 1;
		for (i = 1; i < n; i++) {
			m[a[i]] = 1;
			for (j = 0; j < i; j++) {
				k = (a[i] << 1) - a[j];
				if (k >= 0 && k < n) {
					if (m[k] == 0)
						goto neg;
				}
			}
		}

		printf("yes\n");
		continue;

	neg:
		printf("no\n");
	}

	return 0;
}
