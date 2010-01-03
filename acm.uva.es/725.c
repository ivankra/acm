#include <stdio.h>

char cache[80][1536];

int main()
{
	static int n, k, t, d[10];
	char *p;
	int a, b, i, m;

	for (i = 0; i < 80; i++)
		cache[i][0] = '\0';

	for (t = 0;  scanf("%d", &n) == 1 && n != 0; t++) {
		if (t > 0)
			printf("\n");

		p = cache[n];

		if (*p != '\0') {
			printf("%s", p);
			continue;
		}

		for (b = 1, a = n, k = 0; a <= 99999; b++, a += n) {
			/* a = b * n */

			for (i = 0; i < 10; i++) d[i] = 0;
			for (m = a, i = 0; i < 5; i++, m /= 10) d[m % 10]++;
			for (m = b, i = 0; i < 5; i++, m /= 10) d[m % 10]++;

			for (i = 0; i < 10; i++)
				if (d[i] != 1) break;

			if (i < 10) continue;

			sprintf(p, "%.5d / %.5d = %d\n", a, b, n);
			k++;

			while (*p) p++;
		}

		if (k == 0)
			sprintf(p, "There are no solutions for %d.\n", n);

		printf("%s", cache[n]);
	}

	return 0;
}
