#include <stdio.h>

int main()
{
	int n, d, k, t;

	while (scanf("%d %d", &n, &d) == 2) {
		if ((n % d) == 0) {
			printf("[%d]\n", n / d);
			continue;
		}

		printf("[%d", n / d);
		n %= d;

		for (k = 0; n != 0; k++) {
			putchar((k == 0) ? ';' : ',');

			t = d;
			d = n;
			n = t;

			printf("%d", n / d);

			n %= d;
		}

		printf("]\n");
	}

	return 0;
}
