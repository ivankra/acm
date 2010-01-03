#include <stdio.h>

int main()
{
	static int c[9];
	int i, k, s;

	while (scanf("%d %d %d %d %d %d %d %d %d", &c[8], &c[7], &c[6], &c[5],
		     &c[4], &c[3], &c[2], &c[1], &c[0]) == 9) {

		for (i = 8, s = 0; i > 0; i--) {
			if (c[i] == 0)
				continue;

			k = c[i];

			if (k < 0) {
				k = -k;
				printf(s ? " - " : "-");
			} else if (s != 0) {
				printf(" + ");
			}

			if (k != 1)
				printf("%d", k);

			printf((i == 1) ? "x" : "x^%d", i);
			s = 1;
		}

		if (s == 0)
			printf("%d", c[0]);
		else if (c[0] < 0)
			printf(" - %d", -c[0]);
		else if (c[0] > 0)
			printf(" + %d", c[0]);

		printf("\n");
	}

	return 0;
}
