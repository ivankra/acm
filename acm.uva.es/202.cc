#include <stdio.h>

int main()
{
	int a, b, q[4096], d[4096];
	int i, k, c;

	for (int cs = 1; scanf("%d %d", &a, &b) == 2; cs++) {
		for (i = 0; i < 4096; i++)
			q[i] = 0;

		if (a < b) {
			d[0] = 0;
			i = a;
		} else {
			d[0] = a / b;
			i = a % b;
		}

		for (k = 1; q[i] == 0; k++) {
			q[i] = k;

			i *= 10;
			d[k] = (i / b);
			i %= b;
		}

		c = q[i];

		printf("%d/%d = %d.", a, b, d[0]);

		for (i = 1; i <= 50 && i < k; i++) {
			if (i == c) putchar('(');
			putchar(d[i] + '0');
		}

		if (k > 50)
			printf("...)\n");
		else
			printf(")\n");

		printf("   %d = number of digits in repeating cycle\n", k-c);
		printf("\n");
	}

	return 0;
}
