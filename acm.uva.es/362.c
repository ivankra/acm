#include <stdio.h>

int main()
{
	int a, b, d, n, t, i, k;

	for (d = 1; scanf("%d", &n) == 1 && n > 0; d++) {
		printf("Output for data set %d, %d bytes:\n", d, n);

		for (t = 0, b = 0; b < n;) {
			for (i = k = 0; i < 5 && b < n; i++, t++) {
				scanf("%d", &a);
				b += a;
				k += a;
			}

			if (i < 5)
				break;

			if (k == 0)
				printf("   Time remaining: stalled\n");
			else
				printf("   Time remaining: %d seconds\n",
				       (5 * (n - b) + k - 1) / k);
		}

		printf("Total time: %d seconds\n\n", t);
	}

	return 0;
}
