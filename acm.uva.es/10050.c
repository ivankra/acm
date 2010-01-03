#include <stdio.h>

int main()
{
	static int h[1024], n, p, r, t;
	int i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &p) == 2;) {
		for (i = 0; i < p; i++)
			scanf("%d", &h[i]);

		for (r = 0, i = 0; i < n; i++) {
			if ((i % 7) >= 5) continue;

			for (j = 0; j < p; j++) {
				if (((i + 1) % h[j]) == 0) {
					r++;
					break;
				}
			}
		}

		printf("%d\n", r);
	}

	return 0;
}
